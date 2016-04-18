#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>
using namespace std;
//dynamin_poinnter_cast ???
//vector <string> namesIOfDirs;
class Directory;
class File;

class File
{
	string name; //имя
	string content; //содержание файла
	bool onlyForAdmin;
	bool isOpened;
public:
	File() : onlyForAdmin(false), isOpened(false){};
	File(string name_v) : name(name_v), onlyForAdmin(false), isOpened(false){};
	
	void chmod(bool makeProtected)
	{//установка прав доступа на файл
		if (makeProtected == true)
			onlyForAdmin = true;
		else
			onlyForAdmin = false;
		return;
	}
	void opCl(bool open)
	{
		if (open == true)
			isOpened = true;
		else
			isOpened = false;
		return;
	}
	void writeInFile(string cont)
	{
		if (isOpened == true)
		{
			content = content + " " + cont;
		}
		else
			throw "file isn't opened, cant add info there";//тут будет исключение
		return;
	}
	void cleanFile()
	{
		if (isOpened == true)
		{
			content = "";
		}
		else
			throw "file isn't opened, cant delete content";//тут будет исключение
		return;
	}
	void printFile()
	{
		cout << content;
		return;
	}
	friend Directory;
	~File(){};
};

class Directory
{
	string name;
	Directory* dirs[256]; //массив указателей на директории из данной директории
	File* files[256]; //массив указателей на файлы в этой директории
public:
	Directory(){};
	Directory(string name_v) : name(name_v){/*, dirs{ 0 }, files{0} так нельзя обнулить массив*/
		for (int i = 0; i < 256; i++)
		{
			dirs[i] = nullptr;
		}
		for (int i = 0; i < 256; i++)
		{
			files[i] = nullptr;
		}
	}

	Directory* createDirectory(string name_v)//create
	{//создает новую диркеторию внутри текущей
		int i = 0;
		while (dirs[i] != nullptr)
		{
			i++;
		}
		if (i == 256)
			throw; //тут будет исключение
		else
			dirs[i] = new Directory(name_v);;
		return dirs[i];
	} 
	File* createFile(string name_v) //create
	{
		int i = 0;
		File* obj = new File(name_v);
		while (files[i] != nullptr)
		{
			i++;
		}
		if (i == 256)
			throw; //тут будет исключение
		else
			files[i] = obj;
		return obj;
	} 
	void deleteDirectory(string name_v)
	{//удаляет указанную диркеторию внутри текущей
		int i = 0;
		while (dirs[i]->name != name_v)
		{
			i++;
		}
		delete dirs[i];
		dirs[i] = 0;
	}
	void deleteFile(string name_v, bool suprm)
	{//удаляет указанный файл внутри текущей директории
		int i = 0;
		while (files[i]->name != name_v)
		{
			i++;
		}
		if ((files[i]->onlyForAdmin == true) && (suprm == false))
		{
			cerr << "for deleting this file, you should have administration rights" << endl;
			//здесь будет исключение
		}
		else if (files[i]->isOpened == true)
		{
			cerr << "can't delete this file, cause it's still opened" << endl;
		}
		else
		{
			delete files[i];
				files[i] = 0;
		}
	}
	void printWholeDirectory() //list
	{
		cout << "contents of " << name << endl;
		cout << "directories of "<< name <<":" << endl;
		for (int i = 0; i < 256; i++)
		{
			if (dirs[i] != nullptr)
			{
				cout << dirs[i]->name << endl;
				dirs[i]->printWholeDirectory();
			}
		}
		cout << "files of " <<name << ":"<< endl;
		for (int i = 0; i < 256; i++)
		{
			if (files[i] != nullptr)
				cout << files[i]->name << endl;
		}
	}
	void printDirectory()
	{
		cout << "contents of " << name << endl;
		cout << "directories of " << name << ":" << endl;
		for (int i = 0; i < 256; i++)
		{
			if (dirs[i] != nullptr)
			{
				cout << dirs[i]->name << endl;
			}
		}
		cout << "files of " << name << ":" << endl;
		for (int i = 0; i < 256; i++)
		{
			if (files[i] != nullptr)
				cout << files[i]->name << endl;
		}

	}
	bool ifFileInDirectory(string name_v)
	{//наxодит указанный файл внутри текущей директории, не заходя в лежащие в ней директории
		for (int i = 0; i < filesNum(); i++)
		{
			if (files[i] && files[i]->name == name_v)
				return true;
		}
	}
	bool ifDirectoryInDirectory(string name_v)
	{//наxодит указанную директорию внутри текущей, не заходя в лежащие в ней директории
		for (int i = 0; i < dirsNum(); i++)
		{
			if (dirs[i] && dirs[i]->name == name_v)
				return true;
		}
	}
	Directory* goToDir(string name_v)
	{
		if (ifDirectoryInDirectory(name_v) == true)
		{
			for (int i = 0; i < dirsNum(); i++)
			{
				if (dirs[i]->name == name_v)
					return dirs[i];
			}
		}
		else
		{
			cerr << "no dir with such name in this directory" << endl;
			return NULL;
		}
	}
	int dirsNum()
	{//ищем количество директорий в текущей
		int num = 0;
		for (int i = 0; i < 256; i++)
		{
			if (dirs[i] != nullptr)
				num++;
		}
		return num;
	}
	int filesNum()
	{//ищем количество файлов в текущей директории
		int num = 0;
		for (int i = 0; i < 256; i++)
		{
			if (files[i] != nullptr)
				num++;
		}
		return num;
	}
	File* returnFile(string adr)
	{
		if (ifFileInDirectory(adr) == true)
		{
			for (int i = 0; i < filesNum(); i++)
			{
				if ((files[i])->name == adr)
					return files[i];
			}
		}
		else
		{
			cerr << "no file with such name in this directory" << endl;
			return NULL;
		}
	}
	friend void findFile(string, Directory*, string);//ищем файл по всему дереву
	friend int howManyWords(string, char);
	friend string* breakToWords(string, char);
	friend void deleteWithAddres(Directory*, string);
	friend File;
	~Directory()
	{
		for (int i = 0; i < sizeof(dirs) / sizeof(dirs[0]); i++)
		{
			delete dirs[i];
		}
		for (int i = 0; i < sizeof(files) / sizeof(files[0]); i++)
		{
			delete files[i];
		}
	}
};

void findFile(string name_v, Directory* root, string path) 
{//ищем файл по всему дереву
	path = path + root->name + "/";
	if (root->ifFileInDirectory(name_v) == true)
	{
		cout << endl << path + name_v;
	}
	if (root->dirsNum() != 0)
	{
		for (int i = 0; i < root->dirsNum(); i++)
		{
			findFile(name_v, root->dirs[i], path);
		}
	}
	return;
}
int howManyWords(string str, char separator)
{
	int wordsNum = 1;
	for (unsigned int i = 0; i < str.length(); i++)
	{//посчитали количество разделителей + 1 (2 разделителя -> 3 слова)
		if (str[i] == separator)
		{
			wordsNum++;
		}
	}
	return wordsNum;
}
string* breakToWords(string str, char separator)
{
	string word = "";
	int wordsNum = howManyWords(str, separator);
	cout << wordsNum << endl;
	string* words = new string[wordsNum];
	int k = 0;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == separator)
		{
			words[k] = word;
			k++;
			word = "";
		}
		else
		{
			word += str[i];
		}
	}
	words[k] = word;
	return words;
}
void deleteWithAddres(Directory* root, string adr)
{
	int n = howManyWords(adr, '/');//OK
	string* names = new string[n];//OK
	names = breakToWords(adr, '/');//массив, заполненный названиями директорий в пути + последняя ячейка - название файла
	//(n-1) - количество директорий
	cout << names[n - 1];

	for (int i = 1; i < n-1; i++)
	{
		if (root->ifDirectoryInDirectory(names[i]) == true)
		{
			for (int j = 0; j < root->dirsNum(); j++)
			{
				if ((root->dirs[j])->name == names[i]){
					root = root->dirs[j];
				}
			}
		}
		else
		{
			cerr << "wrong path" << endl;
		}
	}
	root->deleteFile(names[n-1], false);
	delete[] names;
}

void go() {
	cout << "goasjdhjsahdfkjh\n";
}

map<string, void (*)()> g_Commands = {
	{"go", go},
};


int main()
{
	//Directory* dir1 = root->createDirectory("dir1");
	//Directory* dir2 = root->createDirectory("dir2");
	//File* file1 = dir1->createFile("file1");
	//File* file2 = dir1->createFile("file2");
	//File* file7 = dir1->createFile("file3");
	//File* file3 = dir2->createFile("file3");
	//File* file4 = dir2->createFile("file1");
	//Directory* dir3 = dir2->createDirectory("dir3");
	//Directory* dir4 = dir2->createDirectory("dir4");
	//File* file5 = dir4->createFile("file1");
	//File* file6 = dir4->createFile("file4");
	//Directory* dir5 = dir4->createDirectory("dir5");
	//File* file8 = dir5->createFile("file8");
	//
	//file2->chmod(true);
	//dir1->deleteFile("file2");
	//cout << endl << endl << "printWholeDirectory" << endl;
	//dir2->printWholeDirectory();
	//cout << endl << endl;
	//cout << root->dirsNum();
	//cout << endl << "///////////////" << endl;
	////file1->opCl(true);
	//dir1->deleteFile("file1");
	////file1->opCl(false);
	////dir1->deleteFile("file1");
	////dir1->printWholeDirectory();
	//cout << endl << "///////////////" << endl;
	//findFile("file1", root, "");
	//cout << "/////////////////////////" << endl;
	//dir2->deleteDirectory("dir3");
	//cout << endl << endl << "printWholeDirectory" << endl;
	//dir2->printWholeDirectory();
	//cout << endl << endl;
	//deleteWithAddres(root, "root/dir2/dir4/dir5/file8");
	//dir5->printWholeDirectory();
	string str;
	string command = "";
	string adr;
	Directory* root = new Directory("root");
	Directory* thisDir = root;
	bool isProtectedNow = false;
	cout << "This is emulation of file system." << endl << "You are now in 'root'" << endl;
	while (command != "finish")
	{


		cin >> command;
		g_Commands[command]();
		if (command == "mkdir") //создание директории
		{
			cin >> adr;
			thisDir->createDirectory(adr);
		}else
		if (command == "mkfile") //создание файла
		{
			cin >> adr;
			thisDir->createFile(adr);
		}else
		if (command == "tree") //вывод всего дерева
		{
			root->printWholeDirectory();
		}else
		if (command == "chmod") //сделать доступным только администратору
		{
			cin >> adr;
			if (isProtectedNow == false)
			{
			(thisDir->returnFile(adr))->chmod(true);
				isProtectedNow = true;
			}
			else{
				(thisDir->returnFile(adr))->chmod(false);
				isProtectedNow = false;
			}
		}else
		if (command == "rm") //удаление по адресу
		{
			cin >> adr;
			deleteWithAddres(root, adr);
		}else
		if (command == "rm_r") //удаление директории со всем содержимым, внутри текущей директории
		{
			cin >> adr;
			thisDir->deleteDirectory(adr);
		}else 
		if (command == "su_rm") //удаление файла несмотря на администраторские права
		{
			cin >> adr;
			thisDir->deleteFile(adr, true);
		}else 
		if (command == "cd") //перемещение вниз по дереву
		{
			cin >> adr;
			thisDir = thisDir->goToDir(adr);
		}else 
		if (command == "pwd") //показать текущую директорию
		{
			thisDir->printDirectory();
		}else 
		if (command == "list")
		{
			thisDir->printWholeDirectory();
		}else
		if (command == "open")
		{
			cin >> adr;
			(thisDir->returnFile(adr))->opCl(true);
		}else
		if (command == "close")
		{
			cin >> adr;
			(thisDir->returnFile(adr))->opCl(false);
		}else
		if (command == "write")
		{
			string name;
			cin >> name;
			cin >> adr;
			(thisDir->returnFile(name))->writeInFile(adr);
		}else 
		if (command == "clfile")
		{
			cin >> adr;
			(thisDir->returnFile(adr))->cleanFile();
		}else 
		if (command == "read")
		{
			cin >> adr;
			(thisDir->returnFile(adr))->printFile();
		}else 
		if (command == "clc")
		{
			system("cls");
		}else 
		if (command == "find") //ищем файл в текущей директории
		{
			cin >> adr;
			if (thisDir->ifFileInDirectory(adr) != true)
				cout << "this file doesn't exist in this directory" << endl;
			else
				cout << "there is your file in this directory" << endl;
		}else 
		if (command == "find_r") //ищем файла во всем дереве
		{
			cin >> adr;
			findFile(adr, root, "");
		}else
		if (command == "root")
		{
			thisDir = root;
		}
	}
	return 0;
}
