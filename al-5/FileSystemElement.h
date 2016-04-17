#pragma once
#include <string>
#include <iostream>
#include <memory>
//#include "MyFolder.h"

using namespace std;

class MyFolder;
class FileSystemElement
{
protected:
	string name;
	weak_ptr<MyFolder> parent;
public:
	FileSystemElement(string name  = "default_name", weak_ptr<MyFolder> parent = shared_ptr<MyFolder>(nullptr));
	~FileSystemElement(void);

	friend ostream& operator<<(ostream& out_stream, const FileSystemElement& rhs);
};

