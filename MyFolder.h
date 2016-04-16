#pragma once
#include "filesystemelement.h"
#include <memory>
#include <vector>


class MyFolder :
	public FileSystemElement
{
private:
	vector<shared_ptr<FileSystemElement>> element;
public:
	MyFolder(string name  = "default_name", weak_ptr<MyFolder> parent = shared_ptr<MyFolder>(nullptr));
	~MyFolder(void);

	weak_ptr<MyFolder> get_parent_folder_ptr(void) const;
	void add_child(FileSystemElement& child);
	FileSystemElement operator[](int i) { return *element[i]; }
	void list(void) const;
	void createFile(string name, string data) const;
	void remove(FileSystemElement& el);
};
