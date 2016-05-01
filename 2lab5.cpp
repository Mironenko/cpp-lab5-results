// 2lab5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

using namespace std;

class file {
public:
	string name, data;

	file(string a) {
		name = a;
		data = "no_data";
	}

	void open() const {
		cout << name << endl;
		cout << "Data: " << data << endl;
	}

	void write() {
		cout << "Enter new data: ";
		getline(cin, data);
	}

};

class dir {
public:
	string name;

	dir(string a) {
		name = a;
		parent = nullptr;
	}

	vector<shared_ptr<file>> vf;
	vector<shared_ptr<dir>> vd;
	shared_ptr<dir> parent;

	void touch(string a);
	void rm(string a);
	void rmr(string a);
	void list(ostream& out) const;
	void listr(ostream& out) const;
	void write(string a, istream& in);
	void open(string a) const;
	void find(string a, char b);
	void cp(string a, string b);
	void cpr(string a, string b);

	friend void mkdir(string a, shared_ptr<dir> d);
	friend shared_ptr<dir> cd(string a, shared_ptr<dir> d);
	friend void forcpr(shared_ptr<dir> di, shared_ptr<dir> dj);
};

void dir::touch(string a) {
	bool k = false;
	for (int i = 0; i < vf.size() && !k; i++) {
		if (vf[i]->name == a) {
			cout << "Error! There is file with such name in this directory\n";
			k = true;
		}
	}
	if (!k) {
		shared_ptr<file> f(new file(a));
		vf.push_back(static_pointer_cast<file>(f));
	}
}

void dir::rm(string a) {
	bool k = false;
	for (int i = 0; i < vf.size() && !k; i++)
		if (vf[i]->name == a) {
			vf.erase(vf.begin()+i);
			k = true;
		}
	if (!k) cout << "Error! There is no file with such name in this directory\n";
}

void dir::rmr(string a) {
	bool k = false;
	for (int i = 0; i < vd.size() && !k; i++)
		if (vd[i]->name == a) {
			vd.erase(vd.begin()+i);
			k = true;
		}
	if (!k) cout << "Error! There is no directory with such name in this directory\n";
}

void dir::list(ostream& out) const {
	out << name << endl;
	for (int i = 0; i < vd.size(); i++) {
		out << "|___" << vd[i]->name << endl;
	}
	for (int i = 0; i < vf.size(); i++) {
		out << "|___" << vf[i]->name << endl;
	}
}

void dir::listr(ostream& out) const {
	static int a = 0;
	out << name << endl;
	for (int i = 0; i < vd.size(); i++) {
		a++;
		for (int j = 1; j < a; j++) out << "|   ";
		out << "|___";
		vd[i]->listr(out);
		a--;
	}
	for (int i = 0; i < vf.size(); i++) {
		a++;
		for (int j = 1; j < a; j++) out << "|   ";
		out << "|___" << vf[i]->name << endl;
		a--;
	}
}

void dir::write(string a, istream& in) {
	bool k = false;
	for (int i = 0; i < vf.size() && !k; i++) {
		if (vf[i]->name == a) {
			vf[i]->write();
			cout << "Writing succesfully!\n";
			k = true;
		}
	}
	if (!k) cout << "Error! There is no such file\n";
}

void dir::open(string a) const {
	bool k = false;
	for (int i = 0; i < vf.size(); i++) {
		if (vf[i]->name == a) {
			vf[i]->open();
			k = true;
		}
	}
	if (!k) cout << "Error! There is no such file\n";
}

void dir::find(string a, char b) {
	bool k = false;
	if (b == 'r') rm(a);
	if (b == 'o' || b == 'w') {
		for (int i = 0; i < vf.size(); i++) {
			if (vf[i]->name == a) {
				if (b == 'o') vf[i]->open();
				if (b == 'w') vf[i]->write();
				k = true;
			}
		}
		if (!k) cout << "Error! There is no such file\n";
	}
}

void dir::cp(string a, string b) {
	bool k = false, q = false;
	for (int i = 0; i < vf.size() && !k; i++) {
		if (vf[i]->name == a) {
			for (int j = 0; j < vd.size() && !k; j++)
				if (vd[j]->name == b) {
					for (int c = 0; c < vd[j]->vf.size() && !q; c++)
						if (vd[j]->vf[c]->name == a) {
							cout << "Error! Directory already has file with such name\n";
							q = true;
						}
					if (!q) {
						vd[j]->vf.push_back(vf[i]);
						cout << "Copying successfully!\n";
						k = true;
					}
				}
		}
	}
	if (!k && !q) cout << "Error in copying!\n";
}

void dir::cpr(string a, string b) {
	bool k = false, q = false;
	for (int i = 0; i < vd.size() && !k; i++) {
		if (vd[i]->name == a) {
			for (int j = 0; j < vd.size() && !k; j++)
				if (vd[j]->name == b) {
					for (int c = 0; c < vd[j]->vd.size() && !q; c++)
						if (vd[j]->vd[c]->name == a) {
							cout << "Error! Directory already has directory with such name\n";
							q = true;
						}
					if (!q) {
						forcpr(vd[i], vd[j]);
						cout << "Copying successfully!\n";
						k = true;
					}
				}
		}
	}
	if (!k && !q) cout << "Error in copying!\n";
}
	
void forcpr(shared_ptr<dir> di, shared_ptr<dir> dj) {
	static int k = 0;
	shared_ptr<dir> p(new dir(" "));
	p->name = di->name;
	p->vf = di->vf;
	p->parent = dj;
	k++;
	for (int i = 0; i < di->vd.size(); i++) {
		forcpr(di->vd[i], p);
	}
	k--;
	dj->vd.push_back(p);
}

void mkdir(string a, shared_ptr<dir> d) {
	bool k = false;
	for (int i = 0; i < d->vd.size() && !k; i++)
		if (d->vd[i]->name == a) {
			cout << "Error! There is directory with such name in this directory\n";
			k = true;

		}
	if (!k) {
		shared_ptr<dir> p(new dir(a));
		p->parent = d;
		d->vd.push_back(p);
	}
}

shared_ptr<dir> cd(string a, shared_ptr<dir> d) {
	bool k = false;
	for (int i = 0; i < d->vd.size() && !k; i++)
		if (d->vd[i]->name == a) {
			d = d->vd[i];
			k = true;
		}
	if (!k) cout << "Error! There is no such directory\n";
	return d;
}



int main()
{
	shared_ptr<dir> d(new dir(" "));
	shared_ptr<dir> root(new dir("Root"));
	d = root;

	cout << "If you don't know commands, enter 'help' command to view reference\n\n";

	string a, n;
	cin >> a;
	while (a != "exit") {

		if (a == "help") {
			cout << "Some file system emulation (alpha ver.)\nCommands:\nmkdir\t\tcreate directory\ntouch\t\tcreate file\n";
			cout << "rmr\t\tdelete directory with such name (recursive)\nrm\t\tdelete file with such name\nwrite\t\trewrite file data\n";
			cout << "open\t\topen file to read\nfind <> <name>\topen/rewrite/delete file with such name\ncd..\t\tchange directory to parent\n";
			cout << "cd <name>\tchange directory to <name>\ncd\t\tchange directory to root\nlist\t\tshow all files and directories in the current\n";
			cout << "list_r\t\trecursive list\ncp\t\t<what_to_copy>:<where_to_copy>\ncp_r\t\trecursive copying\ndump\t\tdump of file system\n";
		}

		else if (a == "mkdir") {
			cin.ignore();
			getline(cin, n);
			mkdir(n, d);
		}

		else if (a == "touch") {
			cin.ignore();
			getline(cin, n);
			d->touch(n);
		}

		else if (a == "rmr") {
			cin.ignore();
			getline(cin, n);
			d->rmr(n);
		}

		else if (a == "rm") {
			cin.ignore();
			getline(cin, n);
			d->rm(n);
		}

		else if (a == "write") {
			cin.ignore();
			getline(cin, n);
			d->write(n, cin);
		}

		else if (a == "open") {
			cin.ignore();
			getline(cin, n);
			d->open(n);
		}

		else if (a == "find") {
			char b;
			cin.ignore();
			cin >> b;
			cin.ignore();
			getline(cin, n);
			d->find(n, b);
		}

		else if (a == "cd") {
			char b = getchar();
			if (b == '\n') d = root;
			else {
				getline(cin, n);
				d = cd(n, d);
			}
		}

		else if (a == "cd..") {
			if (d->parent != nullptr) d = d->parent;
			else cout << "You are in root directory\n";
		}

		else if (a == "list") {
			d->list(cout);
		}

		else if (a == "list_r") {
			d->listr(cout);
		}
		
		else if (a == "cp") {
			string m;
			cin.ignore();
			getline(cin, n, ':');
			getline(cin, m);
			d->cp(n, m);
		}

		else if (a == "cp_r") {
			string m;
			cin.ignore();
			getline(cin, n, ':');
			getline(cin, m);
			d->cpr(n, m);
		}

		else if (a == "dump") {
			ofstream f("dump.txt");
			root->listr(f);
			f.close();
			cout << "Dumping successfully!\n";
		}

		else cout << "Error! Unknown command\n";

		cin >> a;
	}

	system("pause");
    return 0;
}

