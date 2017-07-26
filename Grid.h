#ifndef GRID_H_
#define GRID_H_
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <tuple>
#include "Storage.h"
using namespace std;

class Grid {
public:
	Grid(string grid_string);
	tuple<map<string,string>,bool> solve();
	tuple<map<string,string>,bool> parse_grid();
	virtual ~Grid();

private:
	Storage str;
	string grid_string;
	map<string,string> grid_values;
	tuple<map<string,string>,bool> values;
	map<string,string> calc_grid_values();

	tuple<map<string,string>,bool> search(tuple<map<string,string>,bool>);
	void assign(tuple<map<string,string>,bool>&, string, string);
	void eliminate(tuple<map<string,string>,bool>&, string, string);

};

#endif /* GRID_H_ */
