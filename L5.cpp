// L5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;
/*
class File
class directoty - создание, размещение в директории содержит массив объектов


*/

class Directory;
class File {
private:
	string mName;
	int content;

public:
	File() {
		content = 0;
		mName = "";
	}

	void set_param(string s, int c) {
		mName = s;
		content = c;
	}




	string name() {
		return mName;
	}



	void see_content() { //надо чтоб возращало int content (вдруг захотим f1.content+f2.content)
		cout << "Значение файла: " << content << endl;
	}

	~File() {}
	//friend class Directory;
};
/*
class Label {

private:
string name;

File *ptrf;
Directory *ptrd;

public:
Label(){
name = "Ярлык";
}

void open_label(){
// тут отобраззить контент на то что указывает ярлык
}

};

*/

class Directory {
	/*  посмотреть имя директории+
	создать файл+
	посмотреть значение файла+
	изменить значение файла ( запись)+(тока значение)
	удалить файл
	...
	ярылки


	*/
private:
	string name_d;
	vector <File> f;
	//vector <string> name_file; // 0- file0 , 1 - file 1,    2 - file2
public:
	Directory() { //не надо не надо
		name_d = "C";
	}
	Directory(string c) {
		name_d = c;
	}

	void see_all_file() {
		for (int i = 0; i < f.size(); i++) {
			cout << f[i].name() << endl;
		}
	}


	void open_file(string s) {
		f[find(s)].see_content();
	}

	void create_file(string s, int c = 0) {
		File a;
		a.set_param(s, c);
		f.push_back(a);
		//name_file.push_back(s);
	}
	void see_d_name() {
		cout << name_d << endl;
	}

	void record(string s, int c) {
		f[find(s)].set_param(s, c);
	}
	void delete_file(string s) {
		f.erase(f.begin() + find(s));
		vector<File>(f).swap(f);

		//name_file.erase(name_file.begin() + find(s)); //тут могут быть ошибки
		//vector<string>(name_file).swap(name_file);

	}


	int find(string c) {

		for (int i = 0; i < f.size(); i++)
		{
			if (f[i].name() == c) return i; //что то тут произошло
		}
		//ошибку не забыть отловить
	}
};

int main(int argc, TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");

	Directory d0; //создание директории по умолчанию
	d0.see_d_name();

	string s;
	string name;
	int content;
	do
	{
		cin >> s;

		if (s == "touch") {
			cout << "Введите имя файла: " << endl;

			cin >> name;
			d0.create_file(name);
		}

		if (s == "list") {
			d0.see_all_file();
		}

		if (s == "open") {
			cout << "Введите имя файла: " << endl;
			cin >> name;
			d0.open_file(name);
		}

		if (s == "write") {
			cout << "Название файла куда записать: "; cin >> name;
			cout << "что знаписать в файл: "; cin >> content;
			d0.record(name, content);
		}

		if (s == "rm") {
			cout << "Какой файл удалить? Имя:"; cin >> name;
			d0.delete_file(name);
		}



	} while (s != "`");


	return 0;
}
