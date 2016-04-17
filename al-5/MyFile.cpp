#include "MyFile.h"


MyFile::MyFile(shared_ptr<MyFolder> parent, string name, string data) : FileSystemElement(parent, name), data(data)
{
}


MyFile::~MyFile(void)
{
}


ostream& operator<<(ostream& out_stream, const MyFile& rhs) {
	cout << rhs.data;


	return out_stream;
}
