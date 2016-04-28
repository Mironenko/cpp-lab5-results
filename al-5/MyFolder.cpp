#include "MyFolder.h"
#include "MyFile.h"
#include "exceptions.h"


MyFolder::MyFolder(shared_ptr<MyFolder> parent, string name) : FileSystemElement(parent, name) {}


MyFolder::~MyFolder(void) {}


void MyFolder::add_child(shared_ptr<FileSystemElement> child) {
	element.push_back(child);

	return;
}


void MyFolder::list(void) const {
	vector<shared_ptr<FileSystemElement>>::const_iterator it;
	for (it = element.cbegin(); it != element.cend(); it++)
		cout << typeid(**it).name() << "\t"  << (*it)->get_name() << endl;
}


vector<weak_ptr<FileSystemElement>> MyFolder::find(string target_name) const {
	vector<weak_ptr<FileSystemElement>> result;
	for (auto el : element)
		if (el->get_name() == target_name)
			result.push_back(el);

	return result;
}