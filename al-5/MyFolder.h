#pragma once
#include "FileSystemElement.h"
#include <memory>
#include <vector>


class MyFolder :
	public FileSystemElement
{
private:
	vector<shared_ptr<FileSystemElement>> element;
public:
	MyFolder(shared_ptr<MyFolder> parent = make_shared<MyFolder>(nullptr), string name = "default_name");
	static shared_ptr<MyFolder> createFolder(shared_ptr<MyFolder> parent = make_shared<MyFolder>(nullptr), string name = "default_name") {
		auto f = make_shared<MyFolder>(parent, name);
		if (parent)
			parent->add_child(dynamic_pointer_cast<FileSystemElement>(f));
		return f;
	}

	~MyFolder(void);

	void add_child(shared_ptr<FileSystemElement> child);
	FileSystemElement operator[](int i) { return *element[i]; }
	void list(void) const;
	
	vector<weak_ptr<FileSystemElement>> find(string target_name) const;
};
