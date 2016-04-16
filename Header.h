#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//#include <algorithm>
using namespace std;

std::vector<std::string>  split(std::string str, std::string splt);


//----- calss FileSys ---- родительский класс
class FileSys {
	FileSys * parent;
	string name;
	string type;
public:
	FileSys();
	FileSys(string, string);
	FileSys(FileSys*, string, string);

	string getName();
	string getType();
	FileSys * getParent();
	//~FileSys();
};

//---- class mFile ---- нужен для инициализации и сопровождения файлов
class mFile : public FileSys {
	string str;
	string * pstr;
public:
	mFile(FileSys*, string);
	mFile(FileSys*, string, int);
	string getStr();
	string * getpStr();
	void Print();
	
	void operator<<(string);
	//~mFile();
};

//----- class Dir ---- нужен для инициализации и сопровождения дирректорий
class Dir : public FileSys {
	vector<FileSys*> * dir;
public:
	Dir();
	Dir(FileSys*, string);

	FileSys * operator()(string);
	FileSys * Find(string);
	FileSys * Create(FileSys*, string, string, FileSys*);
	void Remove(string);
	void List();
	Dir * ChangeDir(string);
	mFile* getFile(string);
	mFile* Copy(string, string, string);
};

class Link : public FileSys {
	FileSys *link;
public:
	Link(string);
	Link(FileSys*, string, FileSys* lnk);
	FileSys * getLink();
};



Link * Find(string, vector<Link*>);
