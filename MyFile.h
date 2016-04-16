#pragma once
#include "filesystemelement.h"
#include "MyFolder.h"
#include <memory>

class MyFile :
	public FileSystemElement
{
private:
	string data;
public:
	MyFile(string data = "", string name  = "blank_file", weak_ptr<MyFolder> parent = shared_ptr<MyFolder>(nullptr));
	~MyFile(void);

	friend ostream& operator<<(ostream& out_stream, const MyFile& rhs);
};

