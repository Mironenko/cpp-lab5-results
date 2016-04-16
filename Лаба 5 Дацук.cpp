#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Base{

};


class Directory: public Base {
public:
	std::string direct;
	std::vector<Base*> list;
	Directory(std::string a) { direct = a; }
};


class File: public Base {
public:
	std::string name;
	std::string content;

	File() { name = ".txt"; content = ' '; }
	File(std::string a, std::string b) { name = a; content = b; }

	File(const File &obj) {}

	~File() {}

};


File create_file()
{
	std::string b, c;
	std::cout << "enter file name" << std::endl;
	std::cin >> b;
	std::cout << "enter file content" << std::endl;
	std::cin >> c;
	File n(b, c);
	return n;
}

Directory create_directory()
{
	std::string a;
	std::cout << "enter directory name" << std::endl;
	std::cin >> a;
	Directory e(a);
	return e;
}

void AddFileToDirectory (Directory a, File* b)
{
	Base* q = static_cast <Base*> (b);
	a.list.push_back(q);
}

int main(int argc, char* argv[])
{
	std::string in;
	int i = 0;
	do {
		std::cout << "Enter command: ";
		std::cin >> in;
		if (in == "CREATE") {
			std::cout << "File or Directory?"; std::cin >> in; if (in == "File") { create_file(); }
																if (in == "Directory") { create_directory(); } };
		if (in == "RM") {};
		if (in == "LIST") {};
	} while (!(in == "END"));
}
