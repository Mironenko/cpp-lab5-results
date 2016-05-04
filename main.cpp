#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class File{
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

	void see_content(){
		cout << "Значение файла: " << content() << endl;
	}

	int content(){
		return nContent;
	}

	~File(){}
};
class Label{
private:
string name;
File *ptrf;

public:
Label(){

}
Label(string s, File* f){
name = s+"_label";
ptrf = f;
}
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
		for (int i = 0; i < f.size(); i++){
			if (f[i].name() == c) return i;
		}
		for (int i = 0; i < label.size(); i++){
			if (label[i].namel() == c) return i;
		}
	}

public:
	Directory(){
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

	void list_files(){
		for (int i = 0; i < f.size(); i++){
			cout << f[i].name() << endl;
		}
	}

    void create_file(string s, int c = 0){
		File a;
		a.set_param(s, c);
		f.push_back(a);
	}

	void open_file(string s){
		cout << f[find(s)].content() << endl;
	}

	void create_label(string s, File* f){
		label.push_back(Label(s, f));

	}

    void open_label(string s){
		File*  f;
		f = label[find(s)].ptrf;
		f->content();
	}

	string d_name()
	{
		return name_d;
	}

	void record(string s, int c)
	{
		f[find(s)].set_param(s, c);
	}

    File* return_ptr(string s){
		return &f[find(s)];
	}
	void delete_file(string s)
	{
		f.erase(f.begin() + find(s));
		vector<File>(f).swap(f);

	}
	
	int find_d(vector<Directory> d, string s){
		for(int i=0; i<d.size();i++){
			if(d[i].d_name()==s) return i;
		}
		
	}
};


int main(){

	setlocale(LC_ALL, "Russian");

	vector<Directory>dir;{
		dir.push_back(Directory("C", 0));
	}

	string s;
	string name;
	string pass;
	string cp ="copy";
	int content;

	int j = 0;

	do
	{
		cin >> s;

		if (s == "touch"){
			cout << "Имя нового файла: " << endl; cin >> name;
			dir[j].create_file(name);
		}
        	if (s == "touchl"){
			cout << "Введите имя файла, ярлык для которого нужно создать: "; cin >> name;
			dir[j].create_label(name, dir[j].return_ptr(name));
		}
		if (s == "list"){
			dir[j].list_files();
		}

		if (s == "open"){
			cout << "Введите имя файла: " << endl; cin >> name;
			dir[j].open_file(name);
		}

		if (s == "write"){
			cout << "Имя файла: "; cin >> name;
			cout << "Содержание файла: "; cin >> content;
			dir[j].record(name, content);
		}

	        if (s == "copy"){
        	cout << "Имя копируемого файла: " << endl; cin >> name;
            	name+=" copy";
            	dir[j].create_file(name);
        	}
		if (s == "rm"){
            	cout << "Для удаления файла введите пароль суперпользователя: "; cin >> pass;
            	if(pass=="qwerty"){
			cout << "Имя удаляемого файла: ";	cin >> name;
			dir[j].delete_file(name);
			}
			else cout << "Неверный пароль" << endl;
		}

		if (s == "newd"){
		cout << "Имя новой директории:"; cin >> name;

		dir.push_back(Directory(name, &dir[j]));
		dir[j].create_nextptr(&dir[j + 1]);
		}

		if (s == "godir"){
			cout << "Имя следюущей директории, к которой перейти: "; cin >> name;
			j = find_d(dir, name);
		}

		if (s == "listdir"){
			for (int i = 0; i < dir.size(); i++){
				cout << dir[j].d_name() << endl;
			}
		}
		if (s == "deldir"){
        	cout << "Для удаления директории введите пароль суперпользователя: "; cin >> pass;
            	if(pass=="qwerty"){
			cout << "Имя директории, которую нужно удалить:"; cin >> name;
			dir.erase(dir.begin() + find_d(dir,name));
			vector<Directory>(dir).swap(dir);
			cout << "Удалено";
			}
			else cout << "Неверный пароль" << endl;
		}
		cout << "=====================================" << endl;

}while (s != "!");

return 0;
}
