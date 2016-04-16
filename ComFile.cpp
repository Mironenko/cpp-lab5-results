#include "StdAfx.h"
#include "ComFile.h"


ComFile::ComFile():name("dafault"),data(0)
{}

ComFile::ComFile(string iname, int idata):name(iname),data(idata)
{}

int ComFile::getData()
{
	return data;
}

void ComFile::setData(int idata)
{
	data=idata;
}
void ComFile::reName(string iname)
{
	name=iname;
}
string ComFile::getName()
{return name;}

ComFile::~ComFile()
{
}
