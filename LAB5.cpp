#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Basic
{
public:
	string name;
};

class File: public Basic
{
	int data;
public:
	File(string n, int d)
	{
		name = n;
		data = d;
	}
	File(string a)
	{
		name = a;
		data = 0;
	}
	~File() {};
};

class Dir : public Basic
{
public:
	Dir(string a)
	{
		name = a;
	}
	vector<shared_ptr<Basic>> vec;
	~Dir() {};
	void create(string n, int d) {
		shared_ptr<File> file(new File(n));
		vec.push_back(static_pointer_cast<Basic>(file));
	}
	void fdel(string a) {
		int k = 0; int i = 0;
		for (auto it = vec.begin(); it != vec.end(); ++it) {
			if ((*it)->name == a) {
				vec.erase(it);
			}
		}
	}
	void list(ostream& out) const {
		out << "Files in " << name << ": " << endl;
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i];
		}
		out << endl;
	}
};

int main()
{
	string n, en;
	cin >> n;
	shared_ptr<Dir> r(new Dir("Root"));
	shared_ptr<File> f(new File(n));
	cin >> n;
	shared_ptr<File> g(new File(n));
	shared_ptr<Dir> q(new Dir("dg"));
	r->vec.push_back(static_pointer_cast<Basic>(f));
	q->vec.push_back(static_pointer_cast<Basic>(f));
	q->vec.push_back(static_pointer_cast<Basic>(g));
	r->list(cout);
	q->list(cout);
	return 0;
}

