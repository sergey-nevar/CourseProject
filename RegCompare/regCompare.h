#pragma once
#include<fstream>
#include<iostream>
#include<vector>
#include"regElement.h"

using namespace std;

class RegCompare
{
	wfstream shot1;
	wfstream shot2;
	vector< RegElement > newHives;
	vector< RegElement > deletedHives;
	vector< RegElement > changedDefaultValues;
	vector< RegElement > changedKeys;
public:
	bool read(wfstream& shot, RegElement& buf);
	void compareShots(char *name1, char *name2);
	void printResults();
	int compareElements(RegElement& element1, RegElement& element2);
	RegCompare(void);
	~RegCompare(void);
};