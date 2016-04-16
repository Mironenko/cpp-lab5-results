#include "Header.h"
using namespace std;

FileSys::FileSys() {
	parent = this;
	name = "object";
	type = "fs";
}

FileSys::FileSys(string nname, string ttype) {
	parent = this;
	name = nname;
	type = ttype;
}

FileSys::FileSys(FileSys * fs, string nname, string ttype) {
	parent = fs;
	name = nname;
	type = ttype;
}

string FileSys::getName()
{
	return name;
}

string FileSys::getType()
{
	return type;
}

FileSys * FileSys::getParent()
{
	return  parent;
}

