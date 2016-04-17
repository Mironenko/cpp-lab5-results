#include "FileSystemElement.h"
#include "MyFolder.h"



using namespace std;


FileSystemElement::FileSystemElement(string name, weak_ptr<MyFolder> parent_) : name(name), parent(parent_) {
	if (parent.lock() != shared_ptr<MyFolder>(nullptr)) {
		parent.lock()->add_child(*this);
	}
}


FileSystemElement::~FileSystemElement(void)
{
}


ostream& operator<<(ostream& out_stream, const FileSystemElement& rhs) {
	cout << rhs.name;

	return out_stream;
}