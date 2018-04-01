#pragma once

#include "map.h"
#include "enumerations.h"
#include <vector>
#include <deque>



using std::vector;
using std::deque;


class position;
class tile;
class map;
class graphics;

typedef vector<tile*> twine;
typedef vector<moveDirection> dirSequence;

class algorithm
{
protected:
	//tileMap virtualMap;
	twine myTwine;
	moveDirection prefdirs[4];
	enumQuarter inQuarter = quarter1;
	enumQuarter fromQuarter;
public:
	algorithm();
	virtual ~algorithm();



	virtual moveDirection nextMove(map& virtualMap, position currpos) = 0;
	tile* getNextTile(map& virtualMap, position currpos, moveDirection dir);
	position getNextPos(position currpos, moveDirection dir);
	virtual dirSequence calcShortestRoute(map virtualMap, position startpos, position endpos);
	void calcPrefDirs(position currpos, position otherpos);
	moveDirection calDirToNextTile(map virtualMap, tile curTile, tile nextTile);
	//int calcAirDistance(position currpos, position endpos);

};

struct helpTile {
	dirSequence dirSeq;
	int length = -1;
	bool finished = false;
};

template <typename T>
typename list<T>::iterator findInList(list<T>& l, T element) {
	typename list<T>::iterator it;
	it = std::find(l.begin(), l.end(), element);
	return it;
}

template list<moveDirection>::iterator findInList<moveDirection>(list<moveDirection>&, moveDirection);


