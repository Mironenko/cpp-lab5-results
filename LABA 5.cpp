// LABA 5 AY.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
class folder;
class file
{
protected:
	string name;
	string dat;
public:
	friend folder;
	file(string n, string d = 0)
	{
		int q = n.length();
		n += ".f";
		name = n;
		dat = d;
	}
};
class folder
{
protected:
	folder* pfol[10];
	file* pfil[10];
	string name;
public:
	folder* rod;
	folder(string n)
	{
		name = n;
		for (int i = 0; i < 10; i++)
		{
			pfol[i] = nullptr;
			pfil[i] = nullptr;
		}
	}
	void created(string n)
	{
		folder* pnew = new folder(n);
		int i = 0;
		while (pfol[i] != 0)
		{
			i++;
		}
		pfol[i] = pnew;
		pnew->rod = this;
	}
	void createf(string n, string d)
	{
		file* pnew = new file(n, d);
		int i = 0;
		while (pfil[i] != 0)
		{
			i++;
		}
		pfil[i] = pnew;
	}
	void remove(string n)
	{
		for (int i = 0; i < 10; i++)
		{
			if (pfol[i]->name == n) pfol[i] = nullptr;
			if (pfil[i]->name == n) pfil[i] = nullptr;
		}
	}
	void list()
	{
		int i = 0;
		cout << "folder:"<< endl;
		while (pfol[i] != 0)
		{
			cout<< pfol[i]->name<<endl;
			i++;
		}
		i = 0;
		cout << "files:" << endl;
		while (pfil[i] != 0)
		{
			cout << pfil[i]->name<<endl;
			i++;
		}
	}
	void print()
	{
		cout << name << ">>";
	}
	void open(string n)
	{
		int i = 0;
		while (pfil[i]->name != n)
		{
			i++;
		}
		cout << pfil[i]->dat<<endl;
	}
	friend void cd(string n);
};



folder headdir("main");
folder* curdir = &headdir;
void cd(string n)
{
	int i = 0;
	while (curdir->pfol[i]->name != n)
	{
		i++;
	}
	curdir = curdir->pfol[i];
}
//cd, mkdir, open, list,
int main()
{
	string data, value, text;
	while (data != "exit")
	{
		curdir->print();
		cin >> data;
		switch (data[0])
		{
		case 'c'://cd
			cin >> value;
			cd(value);
			break;
		case't'://cr file
			cin >> value >> text;
			curdir->createf(value, text);
			break;
		case 'm'://cr dir
			cin >> value;
			curdir->created(value);
			break;
		case 'l'://list
			curdir->list();
			break;
		case '.'://back
			curdir = curdir->rod;
			break;
		case'o'://open
			cin >> value;
			curdir->open(value);
			break;
		default:
			cout << "wrong command"<<endl;
			break;
		}

	}

	return 0;
}
