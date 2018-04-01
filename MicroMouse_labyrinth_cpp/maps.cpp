#include "stdafx.h"
#include "map.h"
#include "maps.h"
#include "position.h"
#include "enumerations.h"
#include "validation.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void setDirectory() {
	SetCurrentDirectoryA("D:\\Production\\Visual Studio 15\\MicroMouse_labyrinth_cpp\\Maps\\");
}

vector<string> openFileList() {
	std::fstream mapListFile;
	mapListFile.open("_mapList.txt");
	int no_maps;
	string next_map;
	vector<string> mapList;

	if (mapListFile.is_open()) {
		mapListFile >> no_maps;
		for (int m = 0; m < no_maps; ++m) {
			mapListFile >> next_map;
			mapList.push_back(next_map);
		}
	}
	else {
		cerr << "could not open maplist file" << endl;
	}	
	sortMapList(mapList);
	return mapList;
}

void sortMapList(vector<string> &mapList) {
	vector<string>::iterator it;
	std::sort(mapList.begin(), mapList.end());
}

void listMaps(vector<string> mapList) {
	cout << "The following maps are in the database:" << endl;
	for (int m = 0; m < mapList.size(); ++m) {
		cout << m + 1 << ": " << mapList.at(m) << endl;
	}
}

map loadMap(vector<string> mapList, int no) {
	std::ifstream mapFile;
	string fileToOpen = mapList.at(no - 1) + ".txt";
	mapFile.open(fileToOpen);
	if (!mapFile.is_open()) cout << "failed to open mapfile" << endl;
	map myMap;
	int x, y;
	mapFile >> myMap.rows >> myMap.columns >> x >> y;
	myMap.setTrepos(position(x, y));
	
	for (int r = 0; r <= myMap.rows + 1; ++r) {
		string tmp;
		getline(mapFile, tmp);
	}

	myMap.initMV();

	
	for (int r = 1; r <= myMap.rows + 1; ++r) {
		for (int c = 1; c <= myMap.columns; ++c) {
			bool tmpwall;
			mapFile >> tmpwall;
			if(r != myMap.rows + 1) myMap.getTile(position(c, r))->setWall(nwall, tmpwall);
			else myMap.getTile(position(c, r - 1))->setWall(swall, tmpwall);

		}
	}

	for (int r = 1; r <= myMap.rows; ++r) {
		for (int c = 1; c <= myMap.columns + 1; ++c) {
			bool tmpwall;
			mapFile >> tmpwall;
			if (c != myMap.columns + 1) myMap.getTile(position(c, r))->setWall(wwall, tmpwall);
			else myMap.getTile(position(c - 1, r))->setWall(ewall, tmpwall);

		}
	}

	
	return myMap;
}

void saveMap(vector<string> &mapList, map &myMap, string savename) {
	
	std::ofstream mapListFile;
	mapListFile.open("_mapList.txt", std::ios_base::trunc);
	if (mapListFile.is_open()) {
		std::vector<string>::iterator it;
	
		it = find(mapList.begin(), mapList.end(), savename);
		if (it != mapList.end()) {
			int input;
			vector<int> possible_int = { 1, 0 };
			do {
				cout << "Overwrite " << savename << "?(1/0)" << endl;
				input = validateInput(possible_int);
				switch (input) {
				case 1:
					break;
				case 0:
					cout << "Enter a different name: ";
					cin >> savename;
					break;
				default:
					break;
				}
			} while (input == ivinput);
		}
		else mapList.push_back(savename);
		
		sortMapList(mapList);

		position trepos = *myMap.getTrepos();
		
		std::ofstream ofile(savename + ".txt");
		ofile << myMap.rows << " " << myMap.columns << " " << trepos.Getx() << " " << trepos.Gety() << endl;
		for (int r = 0; r <= myMap.rows; ++r) {
			for (int c = 1; c <= myMap.columns; ++c) {
				if (r == 0) {
					ofile << " _";
					if (c == myMap.columns) ofile << " ";
				}
				else {
					tile *tmpTile = myMap.getTile(position(c, r));
					if (tmpTile->getWall(wwall)) ofile << "|";
					else ofile << " ";
					if (tmpTile->getWall(swall)) ofile << "_";
					else ofile << " ";
					if (c == myMap.columns) ofile << "|";
				}
			}
			ofile << endl;
		}

		ofile << endl;
		
		
		for (int r = 1; r <= myMap.rows + 1; ++r) {
			for (int c = 1; c <= myMap.columns; ++c) {
				if (r != myMap.rows + 1) {
					tile tmpTile = *myMap.getTile(position(c, r));
					ofile << tmpTile.getWall(nwall) << " ";
				}
				else {
					tile tmpTile = *myMap.getTile(position(c, r - 1));
					ofile << tmpTile.getWall(swall) << " ";
				}
			}
			ofile << endl;
		}

		for (int r = 1; r <= myMap.rows; ++r) {
			for (int c = 1; c <= myMap.columns + 1; ++c) {
				if (c != myMap.columns + 1) {
					tile tmpTile = *myMap.getTile(position(c, r));
					ofile << tmpTile.getWall(wwall) << " ";
				}
				else {
					tile tmpTile = *myMap.getTile(position(c - 1, r));
					ofile << tmpTile.getWall(ewall) << " ";
				}
			}
			ofile << endl;
		}

		ofile.close();
	
		mapListFile << mapList.size() << endl;
		for (int m = 0; m < mapList.size(); ++m) {
			mapListFile << mapList.at(m) << endl;
		}
		mapListFile.close();
		cout << "Save succesful" << endl << endl;
	}
	else cerr << "Failed to open MapListFile" << endl;

	
}

void deleteMaps(vector<string> mapList) {
	vector<int> maps_arr;

	int input;
	vector<int> possible_int = { 1, 0 };
	do {
		cout << endl << "Which maps would you like to delete?" << endl;
		listMaps(mapList);
		cout << endl;
		cout << "Confirm with number 0" << endl << endl;

		int map_no;
		do {
			cin >> map_no;
			if (map_no > 0 && map_no <= mapList.size()) {
				vector<int>::iterator it;
				it = find(maps_arr.begin(), maps_arr.end(), map_no - 1);
				if (it == maps_arr.end()) maps_arr.push_back(map_no - 1);
			}
		} while (map_no != 0);

		cout << "Are you sure you want to delete the following maps?" << endl;
		for (int m = 0; m < maps_arr.size(); ++m) {
			cout << mapList.at(maps_arr[m]) << endl;
		}
		input = validateInput(possible_int);
	} while (input == 0);


	for (int m = 0; m < maps_arr.size(); ++m) {
		remove((mapList.at(maps_arr[m]) + ".txt").c_str());
	}

	vector<string> newMapList;
	for (int m = 0; m < mapList.size(); ++m) {
		vector<int>::iterator it;
		it = find(maps_arr.begin(), maps_arr.end(), m);
		if (it == maps_arr.end()) newMapList.push_back(mapList.at(m));
	}

	std::ofstream mapListFile;
	mapListFile.open("_mapList.txt", std::ios_base::trunc);
	mapListFile << newMapList.size() << endl;
	for (int m = 0; m < newMapList.size(); ++m) {
		mapListFile << newMapList.at(m) << endl;
	}
	mapListFile.close();
}