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
	~MyFile(void);

	MyFile(shared_ptr<MyFolder> parent = shared_ptr<MyFolder>(nullptr), string name = "blank_file", string data = "default_data");
	static shared_ptr<MyFile> createFile(shared_ptr<MyFolder> parent = shared_ptr<MyFolder>(nullptr), string name = "blank_file", string data = "default_data") {
		auto file = make_shared<MyFile>(parent, name, data);
		if (parent)
			parent->add_child(dynamic_pointer_cast<FileSystemElement>(file));
		return file;
	}

	friend ostream& operator<<(ostream& out_stream, const MyFile& rhs);
};

