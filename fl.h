#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
class file
{
private:
  string name;
  int a;
public:
	file(string s1, int b);
    string get_file();
	int get_int();
	void set_int(int b);
	void set_name(string sq);
	~file(void);
};

