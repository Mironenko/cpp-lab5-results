#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class File
{
protected:
	char name, text; // C��������� ����� � ��� �����
public:
	File(char a, char b) // ����������� ����� (��� CREATE)
	{ 
		this->name = a; 
		this->text = b;
	}
	virtual void print() // ������ ����������� ����� (��� CAT)
	{
		cout << "\n Soderzhimoe [" << name << "] :" << text; 
	}
	~File () {} // ���������� ����� (��� RM)

	
};

class Directory
{
protected:
	char name; // �������� ����������
	vector<string> files;
public:
	Directory(char a) // ����������� ���������� (��� CREATE)
	{ 
		this->name = a; 
		
	}
	virtual void print() // ������ ����������� ����� (��� CAT)
	{
		cout << "\n Soderzhimoe [" << name << "] :";
		for (int i=0; i < files.size(); i++) 
		{
			cout << "\n" << files[i];
		}
	}
	
	virtual void add(string c) // ���������� � ���������� �����
	{
	 files.push_back(c);
	}
	
	~Directory () {} // ���������� ���������� (��� RM)

	
};

int main(int argc, char* argv[])
{
	
	return 0;
}
