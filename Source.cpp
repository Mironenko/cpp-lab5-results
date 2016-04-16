#include "Header.h"

std::vector<std::string>  split(std::string str, std::string splt);
using namespace std;

Dir * root = new Dir();
Dir * current = root;
mFile * curFile;
bool tbool1 = true;
vector<Link*> links;

int main() {
	string str = "";
	vector<string> vect;
	cout << "---------- Vlado's Emulated file system v0.00001 ----------" << endl;
	cout << "---------- type 'man' for more information ----------" << endl;
	cout << "strarting emylation..." << endl;
	//----- цикл обработки сообщений
	while (str != "exit") {
		cout << ">>>"; getline(cin, str);
		vect = split(str, " "); if (vect.size() == 0) continue;
		
		//----- блок обработки команд

		if (vect.at(0) == "mkdir") {
			cout << "creating dirrectory... " << endl;
			current->Create(current, vect.at(1), "dir", nullptr);
		}
		if (vect.at(0) == "rm") {
			cout << "removing..." << endl;
			current->Remove(vect.at(1));
		}
		if (vect.at(0) == "list") {
			cout << "objects in this dirrectory:" << endl;
			current->List();
		}
		if (vect.at(0) == "cd") {
			cout << "chaning dirrectory..." << endl;
			current = (Dir *)current->ChangeDir(vect.at(1));
			//cout << vect.at(1) << endl;
		}
		if (vect.at(0) == "open") {
			cout << "opening file..." << endl;
			if(vect.at(1)[0] == '-'){
				curFile = (mFile*)(Find(vect.at(1), links)->getLink());
				//curFile = (mFile*)current->Find(vect.at(1));
				tbool1 = false;
			}
			if(tbool1) curFile = current->getFile(vect.at(1));
			while (str != "close") {
				cout << "file>>>"; getline(cin, str);
				vect = split(str, " "); if (vect.size() == 0) continue;
				if (vect.at(0) == "write") {
					while (str != "-q") {
						getline(cin, str);
						if(str == "-q") break;
						*curFile << str;
						*curFile << "\n";
					}
				}
				else if (vect.at(0) == "cat"){
					curFile->Print();
				}
			}
			tbool1 = true;
		}
		if (vect.at(0) == "touch") {
			current->Create(current, vect.at(1), "file", nullptr);
		}

		if (vect.at(0) == "cat") {
			curFile = current->getFile(vect.at(1));
			curFile->Print();
			curFile = nullptr;
		}
		if (vect.at(0) == "copy"){
			current->Copy(vect.at(1), vect.at(2), "file");
		}
		if(vect.at(0) == "test1"){
			cout << vect.at(0) <<"_" <<endl;
			cout << vect.at(1) <<"_" <<endl;

		}
		if(vect.at(0) == "link"){
			//current->Create(current, vect.at(1), "link", current->Find(vect.at(2)));
			links.push_back((Link*)current->Create(current, vect.at(1), "link", current->Find(vect.at(2))));
			cout << links.at(0)->getName() << " " << links.at(0)->getLink()->getName() << endl;
		}
		



		if(vect.at(0) == "man"){
			string fstr = "";
			ifstream f1;
			f1.open("man.txt");
			while(fstr != "-end"){
				getline(f1, fstr);
				if(fstr == "-end") break;
				cout << fstr << endl;
			}
		}

	}
	return 0;
}




//std::vector<std::string>  split(std::string str, std::string splt) {
//	int i, k, j;
//	std::vector<std::string> v;
//	i = str.find(splt);
//	j = i;
//	//cout << "i is: " << i << endl;
//	if (i == -1 && str.size() != 0) { v.push_back(str.substr(0, str.size() )); }
//	else if (i == -1 && str.size() == 0) return v;
//	else if (i) {
//		v.push_back(str.substr(0, i));
//
//	}
//	 
//	while (true) {
//
//		i = str.find(splt, j + splt.length());
//		
//		if (i == -1 && v.size() > 1) {
//			k = i;
//			if (str.length() - k > 0) { v.push_back(str.substr(k + 1, k - str.length())); }
//			break;
//		}
//		else if (i == -1) {
//			if (str.size() > v.at(0).size()) {
//				//cout << "str size: " << str.size() << endl;
//				//cout << "v size: " << v.at(0).size() << endl;
//				//cout << v.at(0) << endl;
//				v.push_back(str.substr(j, str.size() - 1));
//			}
//			//cout << "else if block" << endl;
//			break;
//		}
//		v.push_back(str.substr(j + splt.length(), i - j));
//		j = i;
//		//k = i;
//	}
//	return v;
//}
