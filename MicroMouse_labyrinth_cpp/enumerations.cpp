#include "stdafx.h"
#include "enumerations.h"

#include <iostream>

using std::cerr;
using std::endl;

enumWalls& operator++(enumWalls &wall, int) {
	if (wall == ivwall) return wall = ivwall;
	int tmp = wall;
	return wall = static_cast<enumWalls>(++tmp);
	
}

moveDirection getDir(enumWalls wall) {
	moveDirection dir = ivdir;
	switch (wall) {
	case nwall:
		dir = ndir;
		break;
	case swall:
		dir = sdir;
		break;
	case wwall:
		dir = wdir;
		break;
	case ewall:
		dir = edir;
		break;
	default:
		cerr << "Invalid parameter for getDir function" << endl;
		break;
	}
	return dir;
}

moveDirection rot90(moveDirection dir, rotDirection rot) {
	moveDirection nextdir = ivdir;
	if (rot == cwise) {
		switch (dir)
		{
		case sdir:
			nextdir = wdir;
			break;
		case ndir:
			nextdir = edir;
			break;
		case edir:
			nextdir = sdir;
			break;
		case wdir:
			nextdir = ndir;
			break;
		case ivdir:
			cerr << "Cannot rotate ivdir" << endl;
			break;
		default:
			cerr << "Invalid input for rot90" << endl;
			break;
		}
	}
	else if (rot == ccwise) {
		switch (dir)
		{
		case sdir:
			nextdir = edir;
			break;
		case ndir:
			nextdir = wdir;
			break;
		case edir:
			nextdir = ndir;
			break;
		case wdir:
			nextdir = sdir;
			break;
		case ivdir:
			cerr << "Cannot rotate ivdir" << endl;
			break;
		default:
			cerr << "Invalid dir input for rot90" << endl;
			break;
		}
	}
	else cerr << "Invalid rot input for rot90" << endl;
	return nextdir;
}

moveDirection operator!(moveDirection dir) {
	//moveDirection nextdir;
	switch (dir)
	{
	case ndir:
		return sdir;
		break;
	case sdir:
		return ndir;
		break;
	case edir:
		return wdir;
		break;
	case wdir:
		return edir;
		break;
	default:
		return ivdir;
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const moveDirection dir) {
	switch (dir) {
	case ndir:
		os << "ndir";
		break;
	case sdir:
		os << "sdir";
		break;
	case edir:
		os << "edir";
		break;
	case wdir:
		os << "wdir";
		break;
	case ivdir:
		os << "ivdir";
		break;
	default:
		break;
	}

	return os;
}