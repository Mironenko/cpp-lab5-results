#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Directory;
class File {
public:
	string name;
	Directory *dir;
}; 

class Directory {
public:
	string dirName;
	Directory *dir;
	vector <Directory> dirv; 
	vector <File> file;
	
	void list()
	{
		cout << "Folders: \n";
		for (int i = 0; i < dirv.size(); i++)
		{
			cout << dirv[i].dirName << endl;
		}
		cout << "Files: \n";
		for (int i = 0; i < file.size(); i++)
		{
			cout << file[i].name << endl;
		}
	}
	
	void createFile()
	{
		File f;
		string namef;
		f.dir = this;
		cout << "Enter file name:";
		cin >> namef;
		f.name = namef;
		file.push_back(f);
	}
	
	void createDir()
	{
		Directory dir;
		string named;
		dir.dir = this;
		cout << "Enter directory name:";
		cin >> named;
		dir.dirName = named;
		dirv.push_back(dir);
	}
};

Directory cd(string a, Directory& folder)
{
	for (int i = 0; i < folder.dirv.size(); i++)
	{
		if (folder.dirv[i].dirName == a)
			return folder.dirv[i];
	}
}

int main()
{
	Directory direc;
	direc.dirName = "root";
	string command, name;

	while (command != "end")
	{
		cin >> command;

		if (command == "list")
			direc.list();
		
		if (command == "cd")
		{
			cin >> name;
			direc = cd(name, direc);
		}
		
		if (command == "createfile")
			direc.createFile();
		
		if (command == "createdir")
			direc.createDir();
		
	}
};
