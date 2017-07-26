#ifndef STORAGE_H_
#define STORAGE_H_
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include <tuple>
#include "Grid.h"
using namespace std;

class Storage {
	friend class Grid;
public:
	Storage();
	virtual ~Storage();
private:
	string digits;
	string rows;
	string cols;
	vector<string> squares;
	vector<string> cross(string, string);
	vector<string> rows_threes;
	vector<string> cols_threes;
	vector<vector<string>> unitlist, unitlist_r,unitlist_c,unitlist_b;
	map<string, vector<vector<string>>> units;
	map<string, set<string>> peers;
	void test();
};

#endif /* STORAGE_H_ */
