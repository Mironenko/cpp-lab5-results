#pragma once
#include "FileSystemElement.h"
#include <memory>
#include <vector>


class MyFolder :
	public FileSystemElement, public enable_shared_from_this<MyFolder>
{
private:
	vector<shared_ptr<FileSystemElement>> element;
public:
	MyFolder(shared_ptr<MyFolder> parent = make_shared<MyFolder>(nullptr), string name = "default_name");
	~MyFolder(void);

	weak_ptr<MyFolder> get_parent_folder_ptr(void) const;
	void add_child(const shared_ptr<FileSystemElement> child);
	FileSystemElement operator[](int i) { return *element[i]; }
	void list(void) const;
	vector<weak_ptr<FileSystemElement>> find(string target_name) const;
};
