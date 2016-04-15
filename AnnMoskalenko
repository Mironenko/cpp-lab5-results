#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Directory;

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
	}
	void opCl(bool open)
	{
		if (open == true)
			isOpened = true;
		else
			isOpened = false;
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
	void deleteFile(string name_v)
	{//удаляет указанный файл внутри текущей директории
		int i = 0;
		while (files[i]->name != name_v)
		{
			i++;
		}
		if (files[i]->onlyForAdmin == true)
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
	bool ifFileInDirectory(string name_v)
	{//наxодит указанный файл внутри текущей директории, не заходя в лежащие в ней директории
		for (int i = 0; i < filesNum(); i++)
		{
			if (files[i]->name == name_v)
				return true;
		}
	}
	bool ifDirectoryInDirectory(string name_v)
	{//наxодит указанную директорию внутри текущей, не заходя в лежащие в ней директории
		for (int i = 0; i < dirsNum(); i++)
		{
			if (dirs[i]->name == name_v)
				return true;
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
	friend void findFile(string, Directory*, string);
	friend int howManyWords(string, char);
	friend string* breakToWords(string, char);
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
	if (root->dirsNum() != 0)
	{
		for (int i = 0; i < root->dirsNum(); i++)
		{
			findFile(name_v, root->dirs[i], path);
		}
	}
	if ((root->ifFileInDirectory(name_v)) != true)
	{
		return;
	}
	else
	{
		cout << endl << path + "/" + name_v;
	}
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

int main()
{
	Directory* root = new Directory("root");
	Directory* dir1 = root->createDirectory("dir1");
	Directory* dir2 = root->createDirectory("dir2");
	File* file1 = dir1->createFile("file1");
	File* file2 = dir1->createFile("file2");
	File* file4 = dir2->createFile("file1");
	File* file3 = dir2->createFile("file3");
	Directory* dir3 = dir2->createDirectory("dir3");



	file2->chmod(true);
	dir1->deleteFile("file2");
	cout << endl << endl << "printWholeDirectory" << endl;
	dir2->printWholeDirectory();
	cout << endl << endl;
	cout << root->dirsNum();
	cout << endl << "///////////////" << endl;

	dir1->deleteFile("file1");

	cout << endl << "///////////////" << endl;
	findFile("file1", root, "");
	cout << "/////////////////////////" << endl;


	system("pause");
	return 0;
}
