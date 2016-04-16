#include <iostream>
#include "MyFolder.h"
#include "MyFile.h"

using namespace std;


int main() {
	shared_ptr<MyFolder> r = make_shared<MyFolder>("root");
	shared_ptr<MyFolder> f1 = make_shared<MyFolder>("folder1", r);
	shared_ptr<MyFolder> f2 = make_shared<MyFolder>("folder2", r);
	shared_ptr<MyFile> fi1 = make_shared<MyFile>("text1", "file1", f1);
	shared_ptr<MyFile> fi2 = make_shared<MyFile>("text2", "file2", f2);

	r->list();
	
	system("pause");
	return 0;
}