#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class File
{
protected:
	char name, text; // Cодержимое файла и имя файла
public:
	File(char a, char b) // Конструктор файла (для CREATE)
	{ 
		this->name = a; 
		this->text = b;
	}
	virtual void print() // Печать содержимого файла (для CAT)
	{
		cout << "\n Soderzhimoe [" << name << "] :" << text; 
	}
	~File () {} // Деструктор файла (для RM)

	
};

class Directory
{
protected:
	char name; // Название директории
	vector<string> files;
public:
	Directory(char a) // Конструктор директории (для CREATE)
	{ 
		this->name = a; 
		
	}
	virtual void print() // Печать содержимого файла (для CAT)
	{
		cout << "\n Soderzhimoe [" << name << "] :";
		for (int i=0; i < files.size(); i++) 
		{
			cout << "\n" << files[i];
		}
	}
	
	virtual void add(string c) // Добавление в директорию файла
	{
	 files.push_back(c);
	}
	
	~Directory () {} // Деструктор директории (для RM)

	
};

int main(int argc, char* argv[])
{
	
	return 0;
}
