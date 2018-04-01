#include "stdafx.h"
#include "position.h"
#include <iostream>

using std::endl;
using std::cerr;



position::position(){
	x = 0;
	y = 0;
}
position::position(int x, int y) :x(x), y(y) {}

int position::Getx() {
	return x;
	/*if (x >= 0) return x;
	else {
		cerr << "Position x not initiated or invalid" << endl;
		return -1;
	}*/
}

int position::Gety() {
	return y;
	/*if (y >= 0) return y;
	else {
		cerr << "Position y not initiated or invalid" << endl;
		return -1;
	}*/
}

void position::Setx(int xin) {
	x = xin;
}

void position::Sety(int yin) {
	y = yin;
}

void position::Incx(int offset) {
	x += offset;
}

void position::Incy(int offset) {
	y += offset;
}

position::~position()
{
}

bool position::operator==(position &pos) {
	if (x == pos.Getx() && y == pos.Gety()) return true;
	else return false;
}

bool position::operator!=(position &pos) {
	if (x != pos.Getx() || y != pos.Gety()) return true;
	else return false;
}