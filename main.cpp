#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Directory;

class File {
private:
	string mName;
	int nContent;

public:
	File(){
		nContent = 0;
		mName = "";
	}

	void set_param(string s, int c){
		mName = s;
		nContent = c;
	}

	string name(){
		return mName;
	}

	void see_content(){ //надо чтоб возращало int content (вдруг захотим f1.content+f2.content)
		cout << "«начение файла: " << content() << endl;
	}

	int content(){
		return nContent;
	}

	~File(){}
	//friend class Directory;
};
/*
class Label {

private:
string name;

File *ptrf;
//Directory *ptrd;

public:
Label(){
name = "ярлык";
}
Label(string s, string names){
	 name = s;
	 
}
void open_label(){
}
friend class Directory;
};
*/


class Directory{

private:
	string name_d;
	vector <File> f;
	Directory *prev, *next;

	int find(string c){

		for (int i = 0; i < f.size(); i++)
		{
			if (f[i].name() == c) return i; 

		}
		
	}



public:
	Directory() {
		name_d = "";

	}
	Directory(string c){
		name_d = c;
	}
	Directory(string c, Directory *prevv){
		name_d = c;
		prev = prevv;
	}

	void create_nextptr(Directory *nextt){
		next = nextt;
	}

	void see_all_file(){
		for (int i = 0; i < f.size(); i++){
			cout << f[i].name() << endl;
		}
	}
	void open_file(string s){
		cout << f[find(s)].content() << endl;
	}

	void create_file(string s, int c = 0){
		File a;
		a.set_param(s, c);
		f.push_back(a);
	}

	string d_name(){
		return name_d;
	}

	void record(string s, int c){
		f[find(s)].set_param(s, c);
	}

	void delete_file(string s){
		f.erase(f.begin() + find(s));
		vector<File>(f).swap(f);

	}

};

int find_d(vector<Directory>, string);

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");


	vector<Directory>dir;
	{
		dir.push_back(Directory("C", 0));
	}
  string s;
	string name;
	int content;

	int ii = 0;

	do
	{
		cin >> s;

		if (s == "touch") {
			cout << "¬ведите им€ файла: " << endl;
			cin >> name;
			dir[ii].create_file(name);
		}

		if (s == "list"){
			dir[ii].see_all_file();
		}

		if (s == "open"){
			cout << "enter file name: " << endl;
			cin >> name;
			dir[ii].open_file(name);
		}

		if (s == "write"){
			cout << "File name to write: ";
			cin >> name;
			cout << "New content ";
			cin >> content;
			dir[ii].record(name, content);
		}

		if (s == "rm"){
			cout << "File to del:";
			cin >> name;
			dir[ii].delete_file(name);
		}
		
		if (s == "newd"){
		cout << "Name of new dir:"; cin >> name;
		
		dir.push_back(Directory(name, &dir[ii]));
		dir[ii].create_nextptr(&dir[ii + 1]);
		}
		
		if (s == "godir"){
			cout << "Dir name to go"; cin >> name;
			ii = find_d(dir, name);
		}

		if (s == "listdir"){
			for (int i = 0; i < dir.size(); i++){
				cout << dir[i].d_name() << endl;
			}
		}
		if (s == "deldir"){
			cout << "Dir name to del:"; cin >> name;

			dir.erase(dir.begin() + find_d(dir,name));
			vector<Directory>(dir).swap(dir);
			cout << "Deleted";
		}

		if (s == "dump"){
			//dir[ii].out;
			ofstream fout("File system.txt");
			for (int i = 0; i < dir.size(); i++){
				fout <<"dir- " << dir[i].d_name() << endl;
			}
			fout.close();
		}
		cout << "-------------------" << endl;
}while (s != "`");
	
	return 0;
}

