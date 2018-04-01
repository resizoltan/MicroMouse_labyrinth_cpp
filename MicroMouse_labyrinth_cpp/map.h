#pragma once



#include <vector>
#include <list>
#include "position.h"


enum enumWalls;
enum moveDirection;

using std::vector;
using std::list;

typedef vector<bool*> wallsvector;
typedef list<moveDirection> nDiscoveredWays;


class tile {
private:
	wallsvector walls;
public:
	bool isDiscovered = false;
	nDiscoveredWays nways;
	position tilePos;


	tile();
	tile(vector<bool> wallin);
	~tile();

	void setWall(enumWalls wid, bool wall);

	bool getWall(enumWalls wid);

	void toggleWall(enumWalls wid);

	void setWallp(enumWalls wid, bool* pwall);

	bool* getWallp(enumWalls wid);
};

typedef vector<tile> row;
typedef vector<row> mapvector;

class map {
private:
	mapvector mv;
	position trepos;
public:
	map();
	map(int rows, int columns);
	map(int rows, int columns, position trepos);
	void initMV();
	tile* getTile(position pos);
	int columns, rows;
	void SetMV(mapvector mvin);

	void setTrepos(position trepos);
	position* getTrepos();
};


