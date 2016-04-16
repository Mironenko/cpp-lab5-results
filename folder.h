#pragma once
#include "fl.h"
#include <vector>
class folder
{
private:
	vector<file> f;
    string name;
public:
	folder(void);
	~folder(void);
	void addf(file f);
	void set_name(string s);
	int get_size();
	file operator()(int index);
};

