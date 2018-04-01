#include "stdafx.h"
#include "map.h"
#include "position.h"
#include "enumerations.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;


map::map() {
	columns = 0;
	rows = 0;
}
map::map(int rows, int columns) :columns(columns), rows(rows) {
	trepos = position(0, 0);
	initMV();
}
map::map(int rows, int columns, position trepos) : columns(columns), rows(rows) {
	this->trepos = trepos;
	initMV();
}


void map::initMV() {
	for (int r = 1; r <= rows; ++r) {
		row newRow;
		for (int c = 1; c <= columns; ++c) {
			tile newTile;
			//if (r == 0 && c == 0) newTile.isDiscovered = true;
			newTile.tilePos.Setx(c);
			newTile.tilePos.Sety(r);
			if (r == 1) newTile.setWallp(nwall, new bool(true));
			else newTile.setWallp(nwall, getTile(position(c, r - 1))->getWallp(swall));

			if (r == rows) newTile.setWallp(swall, new bool(true));
			else newTile.setWallp(swall, new bool(false));

			if (c == 1) newTile.setWallp(wwall, new bool(true));
			else newTile.setWallp(wwall, newRow.at(c-2).getWallp(ewall));

			if (c == columns) newTile.setWallp(ewall, new bool(true));
			else newTile.setWallp(ewall, new bool(false));
			
			newRow.push_back(newTile);
		}
		mv.push_back(newRow);
	}
}

tile* map::getTile(position pos) {
	tile* tmptile;
	if (pos.Getx() >= 1 && pos.Getx() <= columns && pos.Gety() >= 1 && pos.Gety() <= rows) {
		tmptile = &mv.at(pos.Gety() - 1).at(pos.Getx() - 1);
		
	}
	else {
		cout << "Invalid parameters for getTile function" << endl;
		vector<bool> tmpbool = { false, false, false, false };
		tmptile = new tile(tmpbool);
	}
	return tmptile;
}

void map::SetMV(mapvector mvin) {
	mv = mvin;
}

void map::setTrepos(position trepos) {
	this->trepos = trepos;
}

position* map::getTrepos() {
	return &trepos;
}

tile::tile() {
	for (int w = nwall; w <= ewall; w++) {
		walls.push_back(NULL);
	}
	isDiscovered = false;
	tilePos.Setx(0);
	tilePos.Sety(0);
}

tile::tile(vector<bool> wallin) {
	for (int w = nwall; w <= ewall; ++w) {
		walls.push_back(new bool(wallin.at(w)));
	}
	tilePos.Setx(0);
	tilePos.Sety(0);
}

tile::~tile() {
	/*for (int w = nwall; w <= ewall; w++) {
		delete walls.at(w);
		walls.at(w) = NULL;
	}*/
}

void tile::setWall(enumWalls wid, bool wall) {
	*(walls.at(wid)) = wall;
}

bool tile::getWall(enumWalls wid) {
	return *(walls.at(wid));
}

void tile::toggleWall(enumWalls wid) {
	*(walls.at(wid)) = !*(walls.at(wid));
}

void tile::setWallp(enumWalls wid, bool* pwall) {
	walls.at(wid) = pwall;
}

bool* tile::getWallp(enumWalls wid) {
	return walls.at(wid);
}