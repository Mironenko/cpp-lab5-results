#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class ComFile
{
friend ostream& operator<<(ostream &, const ComFile &);//cout
friend istream& operator>>(istream &, ComFile &);//cin
public:
	ComFile();
	ComFile(string , int);
	int getData();
	void setData(int);
	void reName(string);
	string getName();
	
	~ComFile();
private:
	string name;
	int data;
};

