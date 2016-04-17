#include <iostream>|
#include "MyFolder.h"
#include "MyFile.h"

using namespace std;


int main() {
	string cmd;

	shared_ptr<MyFolder> root = make_shared<MyFolder>(shared_ptr<MyFolder>(nullptr), "~");
	shared_ptr<MyFolder> f1 = make_shared<MyFolder>(root, "folder1");
	shared_ptr<MyFolder> f2 = make_shared<MyFolder>(root, "folder2");
	weak_ptr<MyFolder> current_dir = root;

	do
	{
		cout << current_dir.lock()->get_full_path() << " $ ";
		cin >> cmd;

		if (cmd == "ls") {
			current_dir.lock()->list();

		} else if (cmd == "touch") {
			string args;
			getline(cin, args);
			make_shared<MyFile>(current_dir.lock(), args.substr(1, args.length()));

		} else if (cmd == "mkdir") {
			string args;
			getline(cin, args);
			make_shared<MyFolder>(current_dir.lock(), args.substr(1, args.length()));

		} else if (cmd == "find") {
			string args;
			getline(cin, args);
			vector<weak_ptr<FileSystemElement>> result = current_dir.lock()->find(args.substr(1, args.length()));
			for (auto r : result)
				cout << r.lock()->get_name() << endl;
		} else if (cmd == "cat") {
			string args;
			getline(cin, args);
			vector<weak_ptr<FileSystemElement>> element = current_dir.lock()->find(args.substr(1, args.length()));
			/*for (auto el : element) {
				weak_ptr<MyFile> f = el;
				cout << f.lock();
			}*/
		}
	} while (cmd != "exit");
	
	return 0;
}