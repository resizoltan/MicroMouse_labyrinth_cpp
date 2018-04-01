#include "stdafx.h"
#include "algorithm.h"
#include "map.h"
#include "enumerations.h"
#include "graphics.h"


#include <queue>
#include <iostream>
#include <iomanip>


using std::queue;
using std::cout;
using std::endl;
using std::setw;


algorithm::algorithm()
{
}


algorithm::~algorithm()
{
}

dirSequence algorithm::calcShortestRoute(map virtualMap, position startpos, position endpos) {
	vector<vector<helpTile>> helpMap;
	for (int r = 1; r <= virtualMap.rows; r++) {
		vector<helpTile> helpRow;
		for (int c = 1; c <= virtualMap.columns;c++) {
			helpTile ht;
			helpRow.push_back(ht);
		}
		helpMap.push_back(helpRow);
	}

	helpTile* curht = NULL;
	helpTile* ht = NULL;
	//curht->finished = false;
	queue<position> unfinishedTiles;
	unfinishedTiles.push(startpos);
	curht = &helpMap.at(startpos.Getx() - 1).at(startpos.Gety() - 1);
	curht->length = 0;

	position currpos;
	while(unfinishedTiles.size() != 0 && currpos != endpos) {
		currpos = unfinishedTiles.front();
		curht = &helpMap.at(currpos.Getx() - 1).at(currpos.Gety() - 1);
		curht->finished = true;
		tile curTile = *virtualMap.getTile(currpos);
		for (enumWalls w = nwall; w <= ewall; w++) {
			if (curTile.getWall(w) == false)
			{
				position np = getNextPos(currpos, getDir(w));
				helpTile* ht = &helpMap.at(np.Getx() - 1).at(np.Gety() - 1);
				if (ht->finished == false)
				{
					tile tmpTile = *virtualMap.getTile(getNextPos(currpos, getDir(w)));
					if (tmpTile.isDiscovered == true)
					{
						dirSequence ds = curht->dirSeq;
						ds.push_back(getDir(w));
						int length = curht->length + 1;
						helpTile nt = { ds, length };
						if (ht->length == -1 || nt.length < ht->length) *ht = nt;
						unfinishedTiles.push(np);
					}
				}
			}
		}	
		//gfx.drawPos(virtualMap, currpos);
		unfinishedTiles.pop();
	}

	for (int r = 1; r <= virtualMap.rows; ++r) {
		for (int c = 1; c <= virtualMap.columns; ++c) {
			cout << setw(3) << helpMap.at(c - 1).at(r - 1).length;
		}
		cout << endl;
	}

	return helpMap.at(endpos.Getx()-1).at(endpos.Gety()-1).dirSeq;
}

/*int algorithm::calcAirDistance(position currpos, position endpos) {
	int dist = abs(currpos.Getx() - endpos.Getx()) + abs(currpos.Gety() - endpos.Gety());
	return dist;
}*/

void algorithm::calcPrefDirs(position currpos, position otherpos) {
	int cx = currpos.Getx();
	int cy = currpos.Gety();
	int ox = otherpos.Getx();
	int oy = otherpos.Gety();

	if (cx == ox || cy == oy) fromQuarter = inQuarter;

	if (cx < ox && cy < oy) inQuarter = quarter1;
	else if (cx > ox && cy < oy) inQuarter = quarter2;
	else if (cx < ox && cy > oy) inQuarter = quarter3;
	else if (cx > ox && cy > oy) inQuarter = quarter4;


	switch (inQuarter) {
	case quarter1:
		prefdirs[0] = sdir;
		prefdirs[1] = edir;
		prefdirs[2] = wdir;
		prefdirs[3] = ndir;
		break;
	case quarter2:
		prefdirs[0] = sdir;
		prefdirs[1] = wdir;
		if (fromQuarter == quarter1, quarter2) {
			prefdirs[2] = edir;
			prefdirs[3] = ndir;
		}
		else {
			prefdirs[2] = ndir;
			prefdirs[3] = edir;
		}
		break;
	case quarter3:
		prefdirs[0] = ndir;
		prefdirs[1] = wdir;
		if (fromQuarter == quarter1, quarter3) {
			prefdirs[2] = edir;
			prefdirs[3] = sdir;
		}
		else {
			prefdirs[2] = sdir;
			prefdirs[3] = edir;
		}
		break;
	case quarter4:
		prefdirs[0] = ndir;
		prefdirs[1] = wdir;
		if (fromQuarter == quarter2) {
			prefdirs[2] = sdir;
			prefdirs[3] = edir;
		}
		else {
			prefdirs[2] = edir;
			prefdirs[3] = sdir;
		}
		break;
	}
}

position algorithm::getNextPos(position currpos, moveDirection dir) {
	if (dir == ndir) {
		currpos.Incy(-1);
	}
	else if (dir == sdir) {
		currpos.Incy(1);
	}
	else if (dir == edir) {
		currpos.Incx(1);
	}
	else if (dir == wdir) {
		currpos.Incx(-1);
	}
	return currpos;
}

tile* algorithm::getNextTile(map& virtualMap, position currpos, moveDirection dir) {
	currpos = getNextPos(currpos, dir);
	return virtualMap.getTile(currpos);
}

moveDirection algorithm::calDirToNextTile(map virtualMap, tile curTile, tile nextTile) {

	int diffx = nextTile.tilePos.Getx() - curTile.tilePos.Getx();
	int diffy = nextTile.tilePos.Gety() - curTile.tilePos.Gety();
	if (diffx != 0 && diffy != 0) {
		cout << "Not adjacent tile for calDirToNextTile" << endl;
		return ivdir;
	}
	else if (diffx == 0 && diffy == 0) {
		cout << "Same tile for calDirToNextTiel" << endl;
		return ivdir;
	}
	else if (diffx == 1) return edir;
	else if (diffx == -1) return wdir;
	else if (diffy == 1) return sdir;
	else if (diffy == -1) return ndir;



	cout << "Same line, but not adjacent tile for calDirToNextTile" << endl;
	return ivdir;
}







