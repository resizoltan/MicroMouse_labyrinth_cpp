#include "stdafx.h"
#include "map.h"
#include "position.h"
#include "enumerations.h"
#include <conio.h>



bool validPosition(map &myMap, position currpos) {
	return (currpos.Gety() < myMap.rows && currpos.Gety() >= 0 && currpos.Getx() < myMap.columns && currpos.Getx() >= 0);
}

char validateInput(vector<char> possible_char) {
	char inputch = _getch();
	for (int i = 0; i < possible_char.size(); ++i) {
		if (inputch == possible_char[i]) return inputch;
	}

	return 'i';
}

int validateInput(vector<int> possible_int) {
	char inputch = _getch();
	for (int i = 0; i < possible_int.size(); ++i) {
		char tmpch = possible_int[i] + '0';
		if (inputch == tmpch) return possible_int[i];
	}

	return ivinput;
}