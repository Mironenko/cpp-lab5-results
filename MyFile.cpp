#include "MyFile.h"


MyFile::MyFile(string data, string name, weak_ptr<MyFolder> parent) : FileSystemElement(name, parent), data(data)
{
}


MyFile::~MyFile(void)
{
}


ostream& operator<<(ostream& out_stream, const MyFile& rhs) {
	cout << rhs.name << ": " << rhs.data;


	return out_stream;
}
