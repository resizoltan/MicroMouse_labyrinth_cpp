// MicroMouse_labyrinth_cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "main.h"
#include "position.h"
#include "map.h"
#include "enumerations.h"
#include "maps.h"
#include "validation.h"
#include "graphics.h"
#include "algorithm.h"
#include "algo1.h"


#include <conio.h>
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;

template <typename T>
std::string NumberToString(T Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

graphics gfx;

int main()
{
	srand(time(NULL));

	//set working directory for the files
	setDirectory();

	//list of vaailable maps
	vector<string> mapList;

	cout << "Welcome to my MicroMouse labyrinth algorithm!" << endl << endl;

	//declare maps for further processing
	//virtualMap is the labyrinth discovered by the player. at times used for other purposes out of convenience(creating new map ect.)
	map virtualMap;
	//realMap is the actual labyrinth to be discovered. at times used for other purposes out of convenience(random map generator in create mode etc.)
	map realMap;

	bool success = false;
	gfx.initGraphics();


	bool exit = 0;
	int input0;
	do {
		mapList = openFileList();
		cout << endl << "======Main menu======" << endl;
		cout << "Press 1 to play" << endl
			<< "Press 2 to manage maps" << endl
			<< "Press 0 to exit" << endl << endl;
		vector<int> possible_int = { 1, 2, 0 };
		input0 = validateInput(possible_int);
		switch (input0) {
		case 1:
			//enter play mode
			mplay(mapList, virtualMap, realMap);
			break;
		case 2:
			//enter manager mode
			manageMaps(mapList, virtualMap, realMap);
			break;
		case 0:
			//exit application
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	} while (input0 != 0);


    return 0;
}

//if map chosen, launch game, if not chosen, return to main menu
void mplay(vector<string> mapList, map &virtualMap, map &realMap) {
	cout << endl << "------Let's play!------" << endl;
	if (chooseMap(mapList, virtualMap, realMap)) {
		play(virtualMap, realMap);
	}

	
}

//choose and load a map-file. true if chosen, false if cancelled
bool chooseMap(vector<string> mapList, map &virtualMap, map &realMap) {
	cout << "Choose a map" << endl;
	bool valid_map = false;
	do {
		listMaps(mapList);
		cout << endl << "0: Back" << endl << endl;
		int map_no;
		cin >> map_no;
		if (map_no <= mapList.size() && map_no > 0) {
			realMap = loadMap(mapList, map_no);
			virtualMap = map(realMap.rows, realMap.columns);
			valid_map = true;
		}
		else if (map_no == 0) return false;
		else cout << "invalid map number" << endl << endl;
	} while (!valid_map);

	return true;
}

//menu for managing the available maps
void manageMaps(vector<string> mapList, map &virtualMap, map &realMap) {
	int input1;
	do {
		cout << endl << "------Map manager------" << endl;
		cout << "1: Create new map" << endl << "2: Modify map" << endl << "3: Delete map" << endl << endl << "0: Back" << endl;
		vector<int> possible_int = { 1, 2, 3, 0 };
		input1 = validateInput(possible_int);
		switch (input1) {
		case 1: 
			//create new map from scratch. can create new file or overwrite an existing one
			createMap(mapList, virtualMap, realMap, createm);
			break;
		case 2:
			//choose and load a map-file, then modify it. can create new file or overwrite any existing one
			createMap(mapList, virtualMap, realMap, modifym);
			break;
		case 3:
			//choose any map-files to delete
			deleteMaps(mapList);
		case 0:
			//back to main menu
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	} while (input1 == ivinput || input1 != 0);
};

//function executing in play-mode
int play(map &virtualMap, map &realMap) {
	position currpos(1, 1);
	position* trepos = realMap.getTrepos();
	virtualMap.setTrepos(*trepos);
	refreshTile(virtualMap, realMap, currpos);
	//drawMaps(virtualMap, realMap, currpos);

	bool dirpressure;
	cout << "Do you want direction pressure?" << endl;
	cin >> dirpressure;
	algo1 al(virtualMap, dirpressure);
	gfx.drawMaps(virtualMap, realMap, currpos);

	int steps = 0;

	bool end = false;
	char input;
	vector<char> possible_char = { 'w', 's','a', 'd', '0' , '1', 'c', '5'};
	int dir;
	while (!end) {
		//get input direction for moving
		input = validateInput(possible_char);

		//if no valid direction can be determined, direction is invalid
		dir = ivdir;
		switch (input) {
		case 'w':
			dir = ndir;
			break;
		case 's':
			dir = sdir;
			break;
		case 'a':
			dir = wdir;
			break;
		case 'd':
			dir = edir;
			break;
		case '1':
			al.calcShortestRoute(virtualMap, currpos, *trepos);
			break;
		case '5':
			dir = al.nextMove(virtualMap, currpos);
			steps++;
			cout << "steps: " << steps << endl;
			break;
		case 'c':
			virtualMap = realMap;
			for (int c = 1; c <= virtualMap.columns; c++) {
				for (int r = 1; r <= virtualMap.rows; r++) {
					virtualMap.getTile(position(c, r))->isDiscovered = true;
				}
			}
			break;
		case '0':
			end = true;
			break;
		}
		
		//if direction is valid AND not blocked by wall, refresh tile of new position
		if (dir != ivdir && move(virtualMap, currpos, dir)) {
			refreshTile(virtualMap, realMap, currpos);
		}
		//drawMaps(virtualMap, realMap, currpos);
		gfx.drawMaps(virtualMap, realMap, currpos);
	}
	return input + '0';
}

//initialize maps. mode is of enumMode(see "enumerations.h"). return false if cancelled chooseMap in the case of modifying
bool initMaps(vector<string> mapList, map &virtualMap, map &realMap, int mode) {
	cout << endl;
	int rows, columns;
	position trepos;
	int x, y;
	bool valid_data = true;
	if (mode != modifym) {
		do {
			cout << "Please enter the data of the labyrinth:" << endl;
			cout << setw(40) << "Number of rows: "; cin >> rows;
			cout << setw(40) << "Number of columns: "; cin >> columns;
			if (mode == playm) {
				cout << setw(40) << "Position x of treasure: "; cin >> x;
				cout << setw(40) << "Position y of treasure: "; cin >> y;
				trepos = position(x, y);
			}
			valid_data = true;
			if (rows < 0) {
				cout << "invalid number of rows" << endl;
				valid_data = false;
			}
			if (columns < 0) {
				cout << "invalid number of columns" << endl;
				valid_data = false;
			}
			if (mode == playm) {
				if (trepos.Getx() < 0 || trepos.Getx() >= columns) {
					cout << "invalid treasure position x" << endl;
					valid_data = false;
				}
				if (trepos.Gety() < 0 || trepos.Gety() >= rows) {
					cout << "invalid treasure position y" << endl;
					valid_data = false;
				}
			}
			cout << endl;
		} while (!valid_data);
		map tmpMap(rows, columns, trepos);
		virtualMap = tmpMap;
		realMap = tmpMap;
	}
	else {
		if(!chooseMap(mapList, virtualMap, realMap)) return false;
		virtualMap = realMap;
	}

	//createRandomMap(realMap);
	return true;
}

//create a random labyrinth in myMap
void createRandomMap(map &myMap) {
	myMap = map(myMap.rows, myMap.columns);
	for (int r = 1; r <= myMap.rows; ++r) {
		for (int c = 1; c <= myMap.columns; ++c) {
			if (rand() % 2) {
				myMap.getTile(position(c, r))->setWall(nwall, true);
			}
			if (rand() % 2) {
				myMap.getTile(position(c, r))->setWall(wwall, true);
			}
		}
	}
	int x = (rand() % myMap.columns) + 1;
	int y = (rand() % myMap.rows) + 1;
	myMap.setTrepos(position(x, y));
}

//function executing in create-mode. mode is of enumMode
void createMap(vector<string> &mapList, map &virtualMap, map &realMap, enumMode mode) {
	//if cancelled during chooseMap, return to map manager menu
	if(!initMaps(mapList, virtualMap, realMap, mode)) return;

	map emptyMap(virtualMap.rows, virtualMap.columns);
	position currpos(1, 1);
	position* trepos = realMap.getTrepos();

	char inputch;
	gfx.drawMaps(virtualMap, realMap, currpos);

	bool quit = false;
	bool draw = true;
	//move:wasd, toggle walls:4-8-6-2(num pad), copy random map to working map:c, new random map:n, quit:0
	vector<char> possible_char = { 'w', 's', 'a', 'd' , '2', '4', '8', '6', '5' , 'c' , 'n' , '0'};
	do {
		quit = false;
		draw = true;
		inputch = validateInput(possible_char);
		tile *curTile;
		curTile = virtualMap.getTile(currpos);
		switch (inputch) {
		case 'w':
			move(emptyMap, currpos, ndir);
			break;
		case 's':
			move(emptyMap, currpos, sdir);
			break;
		case 'a':
			move(emptyMap, currpos, wdir);
			break;
		case 'd':
			move(emptyMap, currpos, edir);
			break;
		case '4':
			if (currpos.Getx() != 1) {
				curTile->toggleWall(wwall);
			}
			else draw = false;
			break;
		case '8':
			if (currpos.Gety() != 1) {
				curTile->toggleWall(nwall);
			}
			else draw = false;
			break;
		case '6': 
			if (currpos.Getx() != virtualMap.columns) {
				curTile->toggleWall(ewall);
			}
			else draw = false;
			break;
		case '2': 
			if (currpos.Gety() != virtualMap.rows) {
				curTile->toggleWall(swall);
			}
			else draw = false;
			break;
		case '5': *trepos = currpos;
			break;
		case 'c':
			virtualMap = realMap;
			break;
		case 'n':
			createRandomMap(realMap);
			break;
		case '0':
			quit = true;
			draw = false;
			break;
		default:
			draw = false;
			break;
		}
		if(draw) gfx.drawMaps(virtualMap, realMap, currpos);


	} while (!quit);

	virtualMap.setTrepos(*trepos);

	cout << "Would you like to save this map?(1/0)" << endl;
	vector<int> possible_int = { 1, 0 };
	int save_map;
	do {
		save_map = validateInput(possible_int);
		string savename;
		switch(save_map) {
		case 1:
			cout << "Name of file: ";
			cin >> savename;
			saveMap(mapList, virtualMap, savename);
			break;
		case 0:
			cout << "Map discarded" << endl;
			break;
		default:
			cout << "Invalid input" << endl;
			break;
		}
	} while (save_map == ivinput);
}

//sketch maps to console: virtualMap(working map), cursor map, realMap
void drawMaps(map &virtualMap, map &realMap, position currpos) {
	position* trepos = realMap.getTrepos();
	for (int r = 0; r <= virtualMap.rows; ++r) {
		for (int c = 1; c <= virtualMap.columns; ++c){
			if (r == 0) {
				cout << " _";
				if (c == virtualMap.columns) cout << " ";
			}
			else {
				tile *tmpTile = virtualMap.getTile(position(c, r));
				if (tmpTile->getWall(wwall)) cout << "|";
				else cout << " ";
				if (tmpTile->getWall(swall)) cout << "_";
				else cout << " ";
				if (c == virtualMap.columns) cout << "|";
			}
		}
		cout << "  ";
		for (int c = 1; c <= virtualMap.columns; ++c) {
			if (r == 0) cout << "  ";
			else {
				if (currpos == *trepos && currpos.Getx() == c && currpos.Gety() == r) cout << " F";
				else if (currpos.Getx() == c && currpos.Gety() == r) cout << " +";
				else if ((*trepos).Getx() == c && (*trepos).Gety() == r) cout << " X";
				else cout << " O";
			}
		}

		cout << "  ";
		for (int c = 1; c <= realMap.columns; ++c) {
			if (r == 0) {
				cout << " _";
			}
			else {
				tile *tmpTile = realMap.getTile(position(c, r));
				if (tmpTile->getWall(wwall)) cout << "|";
				else cout << " ";
				if (tmpTile->getWall(swall)) cout << "_";
				else cout << " ";
				if (c == realMap.columns) cout << "|";
			}
		}
		cout << endl;
	}
	cout << endl;
}

//move cursor from current position currpos in the direction of dir with one tile. false if direction blocked by wall
bool move(map &virtualMap, position &currpos, int dir) {
	tile *tmpTile = virtualMap.getTile(currpos);

	if (dir == ndir && tmpTile->getWall(nwall) == false) {
		currpos.Incy(-1);
		return true;
	}
	else if (dir == sdir && tmpTile->getWall(swall) == false) {
		currpos.Incy(1);
		return true;
	}
	else if (dir == edir && tmpTile->getWall(ewall) == false) {
		currpos.Incx(1);
		return true;
	}
	else if (dir == wdir && tmpTile->getWall(wwall) == false) {
		currpos.Incx(-1);
		return true;
	}

	return false;
}

//refresh tile of current position(copy wall values from realMap to virtualMap). also refreshes corresponding walls of neighboor tile
void refreshTile(map &virtualMap, map &realMap, position currpos) {
	tile *realTile;
	realTile = realMap.getTile(currpos);
	tile *virtualTile;
	virtualTile = virtualMap.getTile(currpos);
	int rows = virtualMap.rows;
	int columns = virtualMap.columns;
	//virtualTile->isDiscovered = true;
	if (realTile->getWall(nwall) == true) {
		virtualTile->setWall(nwall, true);
	}
	if (realTile->getWall(swall) == true) {
		virtualTile->setWall(swall, true);
	}
	if (realTile->getWall(ewall) == true) {
		virtualTile->setWall(ewall, true);
	}
	if (realTile->getWall(wwall) == true) {
		virtualTile->setWall(wwall, true);
	}
}
