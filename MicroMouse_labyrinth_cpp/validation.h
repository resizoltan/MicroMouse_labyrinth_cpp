#pragma once

#include <vector>
using std::vector;

class map;
class position;

bool validPosition(map &myMap, position currpos);

char validateInput(vector<char> possible_char);

int validateInput(vector<int> possible_int);