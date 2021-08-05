#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include <tuple>
#include <assert.h>
#include "Grid.h"
#include "Storage.h"
using namespace std;

Storage::Storage(): unitlist_r(9,vector<string>(9)),unitlist_c(9,vector<string>(9)),unitlist_b(9,vector<string>(9))
{	//cout << "A Storage instance has been constructed!" << endl;
	digits = "123456789";
	rows = "ABCDEFGHI";
	cols = digits;
	rows_threes = {"ABC","DEF","GHI"};
	cols_threes = {"123","456","789"};
	squares = cross(rows,cols);

	//creating unitlist
	for(int i = 0; i < 9; ++i){
		for(int j = 0; j < 9; ++j){
			unitlist_r[i][j] = cross(rows.substr(i,1),cols)[j];
			unitlist_c[i][j] = cross(rows,cols.substr(i,1))[j];
		}}

	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			for(int k = 0; k < 9; ++k){
				unitlist_b[3*i+j][k] = cross(rows_threes[i],cols_threes[j])[k];
			}}}

	unitlist.insert(unitlist.end(),unitlist_r.begin(),unitlist_r.end());
	unitlist.insert(unitlist.end(),unitlist_c.begin(),unitlist_c.end());
	unitlist.insert(unitlist.end(),unitlist_b.begin(),unitlist_b.end());

	//checking unitlist
	if(false){
		cout << "checking unitlist: " << endl;
		for(int i = 0; i < 27; ++i){
			for(int j = 0; j < 9; ++j){
				cout<< "ith row " << i << " contains: "<< unitlist[i][j] << endl;}}}

	//creating units object
	for(int i = 0; i < 81; ++i){
		for(int j = 0; j < 27; ++j){
			if(find(unitlist[j].begin(),unitlist[j].end(),squares[i]) != unitlist[j].end()){
				vector<string> temp;
				temp = unitlist[j];
				units[squares[i]].push_back(temp);}}}

	//checking units
	if(false){
		cout << "checking units: " << endl;
		for(int i = 0; i < 3; ++i){
				for(int j = 0; j < 9; ++j){
					cout<< i<< "-th row contains: " << units["C2"][i][j] << endl;}}}

	//defining peers
	for(int i = 0 ; i < 81; ++i){
		set<string> temp = {};
		for(int j = 0; j < 3; ++j){
			set<string> insert_set (units[squares[i]][j].begin(),units[squares[i]][j].end());
			temp.insert(insert_set.begin(), insert_set.end());
		}
		temp.erase(squares[i]);
		peers[squares[i]] = temp;
	}

	//checking peers
	if(false){
		cout << "checking peers: " << endl;
		for(int i = 0; i < 81; ++i){
			cout<< squares[i]<< " has peers: " << endl;
			for (string const& peer : peers[squares[i]]){
				cout << peer << endl;}
				}}

	test();

}

vector<string> Storage::cross(string A, string B){
	vector<string> AB(A.length()*B.length());
	for(int i=0; i< A.length(); i++){
		for(int j = 0; j < B.length(); j++){
			AB.at(j+i*B.length()) = A.substr(i,1)+B.substr(j,1);
		}}
	return AB;}

void Storage::test(){
	assert(squares.size() == 81);
	assert(unitlist.size() == 27);
	for(int i = 0; i < squares.size(); ++i){
		assert((units[squares[i]]).size()==3);
		assert((units[squares[i]][0]).size()==9);
		assert((units[squares[i]][1]).size()==9);
		assert((units[squares[i]][2]).size()==9);
	}
	for (int i = 0; i< squares.size(); ++i){
		assert((peers[squares[i]]).size() == 20);
	}
}

Storage::~Storage() {
	//cout << "A Storage instance has been destroyed!"<<endl;
}
