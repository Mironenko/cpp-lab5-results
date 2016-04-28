#include "MyFile.h"



MyFile::MyFile(shared_ptr<MyFolder> parent, string name, string data) : FileSystemElement(parent, name), data(data)
{
	if (parent != shared_ptr<MyFolder>(nullptr)) {
		cout << "*this:\t" << typeid(*this).name() << endl;
		parent->add_child(dynamic_pointer_cast<FileSystemElement>(shared_from_this()));
	}
}


MyFile::~MyFile(void)
{
}


ostream& operator<<(ostream& out_stream, const MyFile& rhs) {
	cout << rhs.data;


	return out_stream;
}
