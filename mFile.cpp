#include "Header.h"
using namespace std;

mFile::mFile(FileSys* parent, string name) 
	:FileSys(parent, name, "file") { str = ""; }

mFile::mFile(FileSys* file, string name, int i):FileSys(file->getParent(), name, "file"){
	str = (((mFile*)file)->getStr());
}

string mFile::getStr(){
	return str;
}

string * getpStr(){
	return nullptr;
}

void mFile::Print(){
	cout << "------ file "  << getName() << " ---------" << endl;
	cout << str << endl;
}

void mFile::operator<<(string strr)
{
	str += strr;
}


