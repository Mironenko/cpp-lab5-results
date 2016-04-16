#include "StdAfx.h"
#include "folder.h"


folder::folder(void)
{
}


folder::~folder(void)
{
}


void folder::addf(file f1)
{
	f.push_back(f1);
}

void folder::set_name(string s)
{
	name=s;
}

int folder::get_size()
{
	return f.size();
}


file folder::operator()(int index)
{
	return f[index];
}