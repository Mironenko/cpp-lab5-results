#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MyFile {
public:
	MyFile();
	MyFile(string, int);
	int getCh();
	void setCh(int);
	string getName();
	void setName(string);
	friend ostream &operator <<(ostream&, MyFile);
	~MyFile();
private:
	string name;
	int ch;
};

ostream &operator <<(ostream& stream, MyFile A) {
	stream << "Имя " << A.name <<endl;
	stream << "Информация " << A.ch << endl;
	return stream;
}

MyFile::MyFile() {
	name = "default";
	ch = 0;
}

MyFile::MyFile(string s, int n) {
	name = s;
	ch = n;
}

int MyFile::getCh() {
	return ch;
}

void MyFile::setCh(int n) {
	ch = n;
}

void MyFile::setName(string s) {
	name = s;
}
string MyFile::getName() {
	return name;
}

class Directory {
public:
	Directory(string ="default");
	void AddFile (MyFile&);
	void DelFile(string);
	void AddDir(Directory&);
	void DelDir(string);
	void DelDir(Directory&);
	void SearchFile(Directory&, string);
	string getName();
	friend ostream &operator <<(ostream&, Directory);
	void print();
	~Directory();

private:
	vector<MyFile> Fl;
	vector<Directory> dir;
	string name;
};

vector<MyFile> rezult;

void Directory::SearchFile(Directory& D, string s) {
	for (int i = 0; i < Fl.size(); i++) {
		if (s == Fl[i].getName()) {
		rezult.push_back(Fl[i]);
		}
	}
	for (int i = 0; i < dir.size(); i++) {
		SearchFile(dir[i], s);
	}
}

void Directory::DelDir(Directory& A) {
	for (int i = 0; i < dir.size(); i++) {
		DelDir(dir[i]);
	}
	Fl.clear();
	dir.clear();
}

string Directory::getName() {
	return name;
}

void Directory::DelDir(string s) {
	for (int i = 0; i < dir.size(); i++) {
		if (s == dir[i].getName()) {
			DelDir(dir[i]);
			break;
		}
	}
}

void Directory::AddDir(Directory& A) {
	dir.push_back(A);
}

Directory::Directory(string s) {
	name = s;
}

Directory::~Directory() {
	Fl.clear();
	dir.clear();
}

void Directory::print() {
	cout << "Файлы " << endl;
	for (int i = 0; i < Fl.size();i++) {
		cout << Fl[i].getName();
	}
	cout << "Директории " << endl;
	for (int i = 0; i < Fl.size(); i++) {
		cout << dir[i].getName();
	}
}

void Directory::AddFile(MyFile& A) {
	Fl.push_back(A);
}

void Directory::DelFile(string s) {
	for (int i = 0; i < Fl.size(); i++) {
		if (s == Fl[i].getName()) {
			Fl.erase(Fl.begin(), Fl.begin() + i);
			break;
		}
	}
}

ostream &operator <<(ostream& stream, Directory A) {
	stream << A.name;
	return stream;
}



int main()
{

    return 0;
}

