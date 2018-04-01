#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

class map;
class position;
class graphics;
enum enumMode;


template <typename T>
std::string NumberToString(T Number);


bool initMaps(vector<string> mapList, map &virtualMap, map &realMap, int mode);

void createRandomMap(map &myMap);

void createMap(vector<string> &maplist, map &virtualMap, map &realMap, enumMode mode);
void drawMaps(map &myMap, map &realMap, position currpos);
int play(map &virtualMap, map &realMap);
bool move(map &myMap, position &currpos, int dir);
void refreshTile(map &virtualMap, map &realMap, position currpos);

void mplay(vector<string> mapList, map &virtualMap, map &realMap);
void manageMaps(vector<string> mapList, map &virtualMap, map &realMap);
bool chooseMap(vector<string> mapList, map &virtualMap, map &realMap);
