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
	FileSystemElement(weak_ptr<MyFolder> parent = make_shared<MyFolder>(nullptr), string name = "default_name");
	~FileSystemElement(void);

	string get_name(void) const { return name; }

	string get_full_path(void) const;
	virtual void remove(void) { this->~FileSystemElement(); }
	friend ostream& operator<<(ostream& out_stream, const FileSystemElement& rhs);
};

