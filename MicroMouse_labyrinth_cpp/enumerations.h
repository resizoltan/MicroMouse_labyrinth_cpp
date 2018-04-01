#pragma once
#include <iostream>

#define ivinput -1

enum enumWalls {
	nwall,
	swall,
	wwall,
	ewall,
	ivwall
};



enum moveDirection {
	sdir,
	ndir,
	edir,
	wdir,
	ivdir
};



enum rotDirection {
	cwise,
	ccwise
};

enum enumMode {
	playm,
	createm,
	modifym
};

enum enumQuarter {
	quarter1,
	quarter2,
	quarter3,
	quarter4
};

enumWalls& operator++(enumWalls& pwall, int);
moveDirection getDir(enumWalls wall);
moveDirection rot90(moveDirection dir, rotDirection rot);
moveDirection operator!(moveDirection dir);
std::ostream& operator<<(std::ostream& os, const moveDirection dir);
