#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include <tuple>
#include <string>
#include "Grid.h"
#include "Storage.h"

using namespace std;
void display(tuple<map<string,string>,bool> values);

int main(){
	//after every nine characters a new line is started to give the Sudoku grid, . means unfilled cells
	Grid grid_1("85...24..72......9..4.........1.7..23.5...9...4...........8..7..17..........36.4.");
	//tuple<map<string,string>,bool> values = grid_1.solve();
	tuple<map<string,string>,bool> values = grid_1.solve();
	display(values);
	return 0;
}

void display(tuple<map<string,string>,bool> values){
	//is the grid solved?
	if(get<1>(values)){cout<< "Solved!"<< endl;}else{cout <<"No solution!"<< endl;}
	//display the grid
	int i = 0;
	std::string underline(106,'_');
	for(auto const& items : get<0>(values)){
		i = i+1;
		size_t t = 9 - items.second.length();
		std::string s(t,' ');
		cout << items.second << s;
		if(i%9 != 0){cout << " | ";}else{
		cout<<endl;
		if(i!=81){
		cout << underline << endl;}
		}}
}
