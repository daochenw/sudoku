#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include <tuple>
#include "Grid.h"
#include "Storage.h"
using namespace std;

Grid::Grid(string x){
	grid_string = x;
	assert(grid_string.length() == 81);
	calc_grid_values();
	get<1>(values) = true;
	for(int i = 0; i < 81; ++i){
		get<0>(values)[str.squares[i]] = str.digits;
	}
	//cout << "A Grid instance has been constructed!" << endl;
}

tuple<map<string,string>,bool> Grid::solve(){
	parse_grid();
	return search(values);
}

tuple<map<string,string>,bool> Grid::search(tuple<map<string,string>,bool> values_){

	if(!get<1>(values_)){
		return values_;}//Failed earlier!
	bool counter = true;
	for(int i = 0; i < 81; ++i){
		counter = counter && (get<0>(values_)[str.squares[i]].length() == 1);
	}
	if(counter){return values_;}//Solved!
	//Choose the unfilled square s with the fewest possibilities
	int temp = 10;
	string s;
	for(int i = 0; i < 81; ++i){
		if((get<0>(values_)[str.squares[i]].length()>1) && (get<0>(values_)[str.squares[i]].length())<temp){
			temp = get<0>(values_)[str.squares[i]].length();
			s = str.squares[i];}
	}

	for(int i = 0; i < get<0>(values_)[s].length(); ++i){
		tuple<map<string,string>,bool> values_copy = values_;
		assign(values_copy,s,get<0>(values_)[s].substr(i,1));
		values_copy = search(values_copy);
		//cout << get<1>(values_copy) << endl;
		if(get<1>(values_copy)){
			return values_copy;}}

	get<1>(values_) = false;
	return values_;
}

tuple<map<string,string>,bool> Grid::parse_grid(){
	for(auto const& items : grid_values){
		if (str.digits.find(items.second) != string::npos)
				{assign(values,items.first,items.second);
				if(!get<1>(values)){return values;}}}
	return values;
}

void Grid::assign(tuple<map<string,string>,bool>& values, string s, string d){
	//cout << "assign is getting called with s=" << s << " and d=" << d << endl;
	string other_values = get<0>(values)[s];
	if (other_values.find(d) != string::npos){
	other_values = other_values.replace(other_values.find(d),d.length(),"");}
	//bool counter = true;
	//note this is the correct implementation of the "all" function due to its short-circuiting feature
	for (int i =  0; i < other_values.length(); ++i){
		eliminate(values,s,other_values.substr(i,1));
		if(!get<1>(values)){
					return;
		}
				}
	return;
}

void Grid::eliminate(tuple<map<string,string>,bool> &values, string s, string d){
	//cout << "eliminate is getting called with s=" << s << " and d=" << d << endl;
	if(get<0>(values)[s].find(d) == string::npos){
		return;
	}

	get<0>(values)[s] = get<0>(values)[s].replace(get<0>(values)[s].find(d),d.length(),"");

	//(1) If a square s is reduced to one value d2, then eliminate d2 from the peers.
	if(get<0>(values)[s].length() == 0){
		get<1>(values) = false;
		return;
	}
	else if(get<0>(values)[s].length() == 1){
		string d2 = get<0>(values)[s];
		for (auto s2 : str.peers[s]){
			//cout << "eliminate is getting called within eliminate" << endl;
			eliminate(values,s2,d2);
			if(!get<1>(values)){
				return;
			}
		}
	}
	//(2) If a unit u is reduced to only one place for a value d, then put it there.

	for(int i = 0; i < 3; ++i){
		vector<string> dplaces = {};
		vector<string> u = str.units[s][i];
		for(int j = 0; j < 9; ++j){
			if(get<0>(values)[u[j]].find(d) != string::npos){
						string temp = u[j];
						dplaces.push_back(temp);}}
		if(dplaces.size() == 0){
			get<1>(values) = false;
			return;
		}

		else if(dplaces.size() == 1){
			//cout << "assign is getting called within eliminate" << endl;
			assign(values,dplaces[0],d);
			if(!get<1>(values)){return;}}}
	return;
}

map<string,string> Grid::calc_grid_values(){
	for(int i = 0; i < 81; ++i){
		grid_values[str.squares[i]] = grid_string.substr(i,1);
	}

	//checking grid_values
	if(false){cout << "checking units: " << endl;
		for(int i = 0; i < 81; ++i){
					cout<< str.squares[i]<< " contains: " << grid_values[str.squares[i]] << endl;}}
	return grid_values;
}


Grid::~Grid() {
	//cout << "A Grid instance has been destroyed!" << endl;
}



