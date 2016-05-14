#include "stdafx.h"
#include <iostream>
#include <windows.h>
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

class Label {

private:
string name;

File *ptrf;
//Directory *ptrd;

public:
Label(){

}
Label(string s, File* f){
name = s+"_label";
ptrf = f;
}


//void open_label(){
// тут отобраззить контент на то что указывает €рлык
	string namel(){
		return name;
	}
	File* f(){
		return ptrf;
	}

friend class Directory;
};



class Directory{

private:
	string name_d;
	vector <File> f;
	vector <Label> label;
	Directory *prev, *next;

	int find(string c){

		for (int i = 0; i < f.size(); i++)
		{
			if (f[i].name() == c) return i; //что то тут произошло

		}
		for (int i = 0; i < label.size(); i++)
		{
			if (label[i].namel() == c) return i;
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
		for (int i = 0; i < label.size(); i++){
			cout << label[i].namel() << endl;
		}
	}


	void open_file(string s){
		cout << f[find(s)].content() << endl;
	}
	void open_label(string s){
		File*  f;
		f = label[find(s)].ptrf;
		f->content();
	}

	void create_file(string s, int c = 0){
		File a;
		a.set_param(s, c);
		f.push_back(a);
	}

	void create_label(string s, File* f){
		label.push_back(Label(s, f));
	
	}

	string d_name(){
		return name_d;
	}

	void record(string s, int c){
		f[find(s)].set_param(s, c);
	}

	File* return_ptr(string s){
		return &f[find(s)];
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
	string copy = " copy";
	string name;
	int content;

	int ii = 0;

	do
	{
		cin >> s;
		/*
		touch
		list
		open
		write
		rm
		newd
		godir
		listdir
		deldir
		copy
		touchl


		*/
	

		if (s == "touch") {
			cout << "¬ведите им€ файла: " << endl;
			
			cin >> name;
			dir[ii].create_file(name);
		}

		if (s == "list"){
			dir[ii].see_all_file();
		}

		if (s == "copy"){
			cout << "¬ведите им€ файла который надо скопировать: " << endl; cin >> name;
			name += " copy";
			dir[ii].create_file(name);
		}
		if (s == "touchl"){
			
			
			cout << "введите им€ файла, которого надо сделать €рлык: "; cin >> name;
			dir[ii].create_label(name, dir[ii].return_ptr(name));
		}

		if (s == "open"){
			cout << "¬ведите им€ файла: " << endl;
			cin >> name;

			if (name.find("_label") != -1){
				dir[ii].open_label(name);
			
			}

			dir[ii].open_file(name);
		}

		if (s == "write"){
			cout << "Ќазвание файла куда записать: ";
			cin >> name;
			cout << "что знаписать в файл: ";
			cin >> content;
			dir[ii].record(name, content);
		}

		if (s == "rm"){
			cout << " акой файл удалить? »м€:";
			cin >> name;
			dir[ii].delete_file(name);
		}

		if (s == "newd"){
			cout << "—оздание новой директории, им€:"; cin >> name;

			dir.push_back(Directory(name, &dir[ii]));
			dir[ii].create_nextptr(&dir[ii + 1]);
		}

		if (s == "godir"){
			cout << "  какой директории перейти? им€:"; cin >> name;
			ii = find_d(dir, name);
		}

		if (s == "listdir"){
			for (int i = 0; i < dir.size(); i++){
				cout << dir[i].d_name() << endl;
			}
		}
		if (s == "deldir"){
			cout << "им€ директории которую удалить:"; cin >> name;

			dir.erase(dir.begin() + find_d(dir, name));
			vector<Directory>(dir).swap(dir);
			cout << "”далено";
		}
		

		cout << "=====================================" << endl;
	} while (s != "`");



	return 0;
}

int find_d(vector<Directory> d, string s){ //тут надо передать не сам d а тока ссылку на него но хз как
	for (int i = 0; i < d.size(); i++){
		if (d[i].d_name() == s) return i;
	}//ошибку не забыть отловить
}
