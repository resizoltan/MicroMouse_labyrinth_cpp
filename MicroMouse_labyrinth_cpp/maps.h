#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

void setDirectory();

vector<string> openFileList();

class map;
class position;

void listMaps(vector<string> mapList);

void sortMapList(vector<string> &mapList);

map loadMap(vector<string> mapList, int no);

void saveMap(vector<string> &mapList, map &myMap, string savename);

void deleteMaps(vector<string> mapList);