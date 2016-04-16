// 2lab5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class basic {
public:
	string name;

	void print(ostream& out) const {
		out << name << endl;
	}
};

class file: public basic {
public:
	int data;

	file(string a, int b) {
		name = a;
		data = b;
	}

	file(string a) {
		name = a;
		data = 0;
	}
};

class dir: public basic {
public:
	dir(string a) {
		name = a;
	}

	vector<shared_ptr<basic>> v;


	void add() {
		int i;
		string a;
		cout << "Enter the name of file: ";
		cin >> a;
		cout << "Enter data: ";
		cin >> i;
		shared_ptr<file> f(new file(a, i));
		v.push_back(static_pointer_cast<basic>(f));
	}


	void fdel(string a) {
		int k = 0; int i = 0;
		for (auto it = v.begin(); it != v.end(); ++it) {
			if ((*it)->name == a) {
				v.erase(it);
			}
		}
	}


	void list(ostream& out) const {
		out << "Files in " << name << ": " << endl;
		for (int i = 0; i < v.size(); i++) {
			v[i]->print(out);
		}
		out << endl;
	}

};


int main()
{
	string n, en;
	cin >> n;
	shared_ptr<dir> r(new dir("Root"));
	shared_ptr<file> f(new file(n));
	cin >> n;
	shared_ptr<file> g(new file(n));
	shared_ptr<dir> q(new dir("dg"));
	r->v.push_back(static_pointer_cast<basic>(f));
	q->v.push_back(static_pointer_cast<basic>(f));
	q->v.push_back(static_pointer_cast<basic>(g));
	r->list(cout);
	q->list(cout);
    return 0;
}

