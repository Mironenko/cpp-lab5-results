#include <iostream>
#include "MyFolder.h"
#include "MyFile.h"

using namespace std;


int main() {
	string cmd;
	string args = "";

	shared_ptr<MyFolder> root = make_shared<MyFolder>("~");
	shared_ptr<MyFolder> f1 = make_shared<MyFolder>("folder1", root);
	shared_ptr<MyFolder> f2 = make_shared<MyFolder>("folder2", root);
	weak_ptr<MyFolder> current_dir = root;

	do
	{
		cout << current_dir.lock()->get_full_path() << " $ ";
		cin >> cmd;
		if (cmd == "list") {
			current_dir.lock()->list();
		} else if (cmd == "touch") {
			getline(cin ,args);
			make_shared<MyFile>("test", args, current_dir);
		}
	} while (cmd != "exit");
	
	system("pause");
	return 0;
}