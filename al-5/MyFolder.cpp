#include "MyFolder.h"
#include "MyFile.h"


MyFolder::MyFolder(weak_ptr<MyFolder> parent, string name) : FileSystemElement(parent, name) {
}


MyFolder::~MyFolder(void)
{
}


weak_ptr<MyFolder> MyFolder::get_parent_folder_ptr(void) const { return parent; }


void MyFolder::add_child(FileSystemElement& child) {
	element.push_back(make_shared<FileSystemElement>(child));

	return;
}


void MyFolder::list(void) const {
	std::vector<shared_ptr<FileSystemElement>>::const_iterator it;
	for (it = element.cbegin(); it != element.cend(); it++)
		cout << **it << endl;
}


void MyFolder::createFile(string name, string data) const {
	make_shared<MyFile>(make_shared<MyFolder>(*this), name, data);

	return;
}


void MyFolder::remove(FileSystemElement& el) {

	return;
}
