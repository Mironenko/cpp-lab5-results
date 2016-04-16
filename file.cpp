#include "StdAfx.h"
#include "fl.h"


file::file(string s1, int b)
{
	name=s1;
	a=b;
}


file::~file(void)
{
}


string file::get_file()
{
	return name;
}


int file::get_int()
{
	return a;
}

void file::set_name(string s1)
{
	name=s1;
}


void file::set_int(int b)
{
	a=b;
}