#include "stdafx.h"
#include "algo1.h"
#include "enumerations.h"
#include "position.h"
#include "map.h"
#include <iostream>

using std::cout;
using std::endl;

algo1::algo1(map& virtualMap, bool dirpressure):dirpressure(dirpressure)
{
	tile* tmpTile;
	tmpTile = virtualMap.getTile(position(1, 1));
	myTwine.push_back(tmpTile);
	trepos = *virtualMap.getTrepos();

	/*position currpos = position(1, 1);
	tile* curTile = virtualMap.getTile(currpos);
	layTwine(*curTile);
	calcPrefDirs(currpos, *virtualMap.getTrepos());*/
}


algo1::~algo1()
{
}

moveDirection algo1::nextMove(map& virtualMap, position currpos) {
	tile* curTile;
	curTile = virtualMap.getTile(currpos);
	tile* prevTile = NULL;
	moveDirection nextDir;
	
	if (curTile->isDiscovered == false) {
		curTile->isDiscovered = true;
		for (enumWalls w = nwall; w <= ewall; w++) {
			if (curTile->getWall(w) == false){
				tile* nt;
				nt = getNextTile(virtualMap, currpos, getDir(w));
				list<moveDirection>::iterator it;
				if (nt->isDiscovered == false) {
					curTile->nways.push_back(getDir(w));
					//cout << "New nway: " << w << endl;
				}
				else {
					it = findInList(nt->nways, !getDir(w));
					if(it != nt->nways.end())
						nt->nways.erase(it);
				}
			}
		}
	}
	if (curTile->nways.size() > 0) {
		if (dirpressure) {
			nextDir = ivdir;
			calcPrefDirs(currpos, trepos);
			cout << "prefdir0: " << prefdirs[0] << ", prefdir1: " << prefdirs[1] << ", prefdir2: " << prefdirs[2] << ", prefdir3: " << prefdirs[3] << endl;
			list<moveDirection>::iterator it;
			//it = findInList(curTile->nways, prefdirs[0]);
			for (int i = 0; i < 4; i++) {
				if ((it = findInList(curTile->nways, prefdirs[i])) != curTile->nways.end()) {
					nextDir = prefdirs[i];
					curTile->nways.erase(it);
					break;
				}
			}
			if (nextDir == ivdir) {
				nextDir = curTile->nways.front();
				curTile->nways.pop_front();
			}
		}
		else {
			nextDir = curTile->nways.front();
			curTile->nways.pop_front();
		}
		myTwine.push_back(virtualMap.getTile(getNextPos(currpos, nextDir)));
		//cout << "new pos: " << getNextPos(currpos, nextDir).Getx() << " " << getNextPos(currpos, nextDir).Gety() << endl;
	}
	else {
		if (myTwine.size() > 1) {
			myTwine.pop_back();
			prevTile = myTwine.back();
			nextDir = calDirToNextTile(virtualMap, *curTile, *prevTile);
			cout << "Back to prev tile of myTwine" << endl;
		}
		else {
			cout << "myTwine is zero. Map should be fully discovered" << endl;
			nextDir = ivdir;
		}
	}
	return nextDir;
}








