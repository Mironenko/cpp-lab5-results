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
	FileSystemElement(weak_ptr<MyFolder> parent = shared_ptr<MyFolder>(nullptr), string name = "default_name");
	~FileSystemElement(void);

	string get_full_path(void) const;
	friend ostream& operator<<(ostream& out_stream, const FileSystemElement& rhs);
};

