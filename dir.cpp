#include "Header.h"
using namespace std;

Dir::Dir() :FileSys("root", "dir") { dir = new vector<FileSys*>; }

Dir::Dir(FileSys* parent, string name) : FileSys(parent, name, "dir") { dir = new vector<FileSys*>; }

FileSys * Dir::operator()(string name){
		for (int i(0); i < dir->size(); i++) {
		if (name == dir->at(i)->getName()) {
			return dir->at(i);
		}
	}
}

FileSys * Dir::Find(string name){
	for (int i(0); i < dir->size(); i++) {
		if (name == dir->at(i)->getName()) {
			return dir->at(i);
		}
	}
	
}

FileSys * Dir::Create(FileSys* fs, string name, string type, FileSys * lnk = nullptr)
{
	if (type == "dir") {
		FileSys * newitem = new Dir(fs, name);
		dir->push_back(newitem);
		cout << "dir "<< name <<" created" << endl;
		return newitem;
	}
	else if (type == "file") {
		FileSys * newitem = new mFile(fs, name);
		dir->push_back(newitem);
		cout << "file " << name << " created" << endl;
		return newitem;
	}
	else if (type == "link") {
		FileSys * newitem = new Link(fs, "-"+name, lnk);
		dir->push_back(newitem);
		cout << "link " << name << " created" << endl;
		return newitem;
	}
	return nullptr;
}

void Dir::Remove(string name) {
	for (int i(0); i < dir->size(); i++) {
		if (name == dir->at(i)->getName()) delete dir->at(i);
	}
	cout << "object " << name << " removed" << endl;
}

void Dir::List()
{

	for (int i = 0; i < dir->size(); i++) {
		cout << dir->at(i)->getType()<< " " << dir->at(i)->getName() << endl;
	}
}

Dir * Dir::ChangeDir(string name)
{
	if (name == "../") return (Dir *)getParent(); //<--------------
	for (int i(0); i < dir->size(); i++) {
		
		if (name == dir->at(i)->getName()) {
			return (Dir *)dir->at(i);
		}
	}
	
}

mFile * Dir::getFile(string name)
{
	for (int i(0); i < dir->size(); i++) {
		if (name == dir->at(i)->getName()) {
			return (mFile *)dir->at(i);
		}
	}
	return nullptr;
}

mFile * Dir::Copy(string name1, string name2, string type){
	FileSys* temp = Find(name1);
	


	/*if (type == "dir") {
		FileSys * newitem = new Dir(fs, name);
		dir->push_back(newitem);
		cout << "dir "<< name <<" created" << endl;
		return newitem;
	}*/


	if (type == "file" && temp != nullptr) {
		FileSys * newitem = new mFile((mFile*)temp, name2, 1);
		dir->push_back(newitem);
		cout << "file " << name1 << " copyed" << endl;
		return (mFile*)newitem;
	}
	/*else if (type == "link") {
		FileSys * newitem = new Link(fs, name);
		dir->push_back(newitem);
		cout << "link " << name << " created" << endl;
		return newitem;
	}*/
	return nullptr;
}

