#include "FileSystemElement.h"
#include "MyFolder.h"



using namespace std;


FileSystemElement::FileSystemElement(shared_ptr<MyFolder> parent, string name) : name(name), parent(parent) {
	if (parent != shared_ptr<MyFolder>(nullptr)) {
		parent->add_child(*this);
	}
}


FileSystemElement::~FileSystemElement(void)
{
}


ostream& operator<<(ostream& out_stream, const FileSystemElement& rhs) {
	cout << rhs.name;

	return out_stream;
}


string FileSystemElement::get_full_path(void) const {
	string path;
	if (name == "~")
		path = name;
	else
		path = parent->get_full_path() + "/" + name;
	return path;
}