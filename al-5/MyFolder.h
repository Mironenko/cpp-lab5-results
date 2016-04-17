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
	MyFolder(weak_ptr<MyFolder> parent = shared_ptr<MyFolder>(nullptr), string name = "default_name");
	~MyFolder(void);

	weak_ptr<MyFolder> get_parent_folder_ptr(void) const;
	void add_child(FileSystemElement& child);
	FileSystemElement operator[](int i) { return *element[i]; }
	void list(void) const;
	vector<shared_ptr<FileSystemElement>> find(string target_name) const;
};
