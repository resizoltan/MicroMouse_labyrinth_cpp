#pragma once
#include "algorithm.h"

class position;
class map;
class tile;
enum moveDirection;
enum rotDirection;



class algo1 :
	public algorithm
{
private:
	rotDirection prefrot;
	position trepos;
	bool dirpressure = true;
	

public:
	algo1(map& virtualMap, bool dirpressure);
	~algo1();

	moveDirection nextMove(map& virtualMap, position currpos);
};

