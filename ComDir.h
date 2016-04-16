#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "ComFile.h"
using namespace std;

class ComDir
{
friend class ComFile;
friend ostream& operator<<(ostream &, const ComDir &);//cout
friend istream& operator>>(istream &, ComDir &);//cin

public:
	ComDir();
	ComDir(string);
	string getName();
	void addFile(ComFile &);
	void addDir(ComDir &);
	void ListAll();
	void delFile(string);
	void delDir(string);
	void search(ComDir &,string); 
	void ComDir::delDir(ComDir &);
	~ComDir();
private:
	string name;
	vector<ComDir> dirList;
	vector<ComFile> fileList;
};
vector<ComFile> result;
void ComDir::search(ComDir &dir1,string iname)
{
	for(int i=0;i<fileList.size();i++)
	{
		if(fileList[i].getName()==iname)
			result.push_back(fileList[i]);

	}
	for(int i=0; i<dirList.size();i++)
		search(dirList[i],iname);
}
