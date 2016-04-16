#include <iostream>
#include <stdexeption>
#include <string>
#include <memory>

using namespace std;

Class AbstractClass{
protected:
	Directory parentDir;
	string name;
	string path;
public:
	AbstactClass(Directory* _parentDir, string _name){
		parentDir = _parentDir;
		name = _name;
		strcat(path, parentDir -> path);
		strcat(path, name);
	}
	virtual 
	virtual ~AbstractClass();
};

Class File: virtual public AbstractClass{
private:
	string data;
public:

};

Class Directory: virtual public AbstractClass{
private:
	vector <Directory*> childDirs;
	vector <File*> files;
public:
	static Directory* rootDir;
	Directory(string _name){
		if (rootDir == nullptr){
			parentDir = nullptr;
			rootDir = this;
			name = _name;
			path = _name;
		}
		else
			throw();
	}
	Directory(Directory* _parentDir, string _name): AbstactClass(Directory* _parentDir, string _name){	
	}
	~Directory(
};