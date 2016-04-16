//DISCLAMER:
//Данный код состоит из исключений чуть менее, чем полностью. Данная реализация может оказаться не до конца понятной, 
//а так же Вам может показаться, что это писал невминяемый человек, либо же, что сие творение было написано внеземным разумом
//Так или иначе, чтение этого кода может привести к навязчевому желанию выдрать себе глаза в процессе чтения или
//убить того, кто это сделал, а так же, вероятно, вызывает психоз и эпелиптические припадки.
//Попробуйте прочитать код 
//Если у вас в процессе чтения болит голова или глаза, участилось сердцебиение или вы вовсе не понимаете, что это такое
//	То немедленно прекратите читать код
//Исключением является случай, если Вы - преподаватель, который ведет лабы у этого невменяемого индуса
//Британские ученые подсчитали, что на написание этого кода ушло от 8 до 10 часов

//Viewer discretion is advised 
//(C)ShiftDj, 2016
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

class accessDeniedException : public exception {};
class directoryChangeException : public exception {};
class fileNotFoundException : public exception {};
class fileExistsException : public exception {};
class filePathIncorrectException : public exception {};
class directoryIsFileException : public exception {};
class fileNotOpenedException : public exception {};
class fileNotClosedException : public exception {};
class dumpUnsuccessfulException : public exception {};
class directoryRemoveException : public exception {};

//vfsunit
//file : vfsunit
//directory : vfsunit
//link : vfsunit
//VFS {vector<vfsunit*>} vfs;

class vfsunit {
	protected:
	string path;
	string name;
	string content;
	//0 - can't read and write
	//1 - can read
	//2 - can write
	//3 - can read and write
	char mod;  
	char type;
	public:
	vfsunit() = delete;
	vfsunit(string Path, string Name, string Content, char Mod, char Type) : path(Path), name(Name), content(Content), mod(Mod), type(Type) {};
	vfsunit(const vfsunit& O) : path(O.path), name(O.name), content(O.content), mod(O.mod), type(O.type) {};
	string getName();
	void setName(string Name);
	string getPath();
	char getMod();
	void setMod(char Mod);
	char getType();
	virtual string getContent() {throw logic_error("Vitrual getContent() must not to be used"); return "";};
	virtual void setContent(string Content) {throw logic_error("Vitrual setContent() must not to be used");};
};

class VFS {
	vector <vfsunit*> files;
	vfsunit *lock;
	char lockmod;
	public:
	VFS() {
		lock = nullptr;
	};
	vfsunit& getFile(string PathName);
	void addFile(string PathName, string Content, char Mod, char type);
	void copyFile(string PathName, string NewPath);
	void copyFiles(string Path, string NewPath);
	void deleteFile(string PathName);
	void deleteFileSu(string PathName);
	void deleteRecursive(string PathName);
	vector<string> getFiles(string path);
	vector<string> findFile(string name);
	void checkDirectory(string path, char mod);
	void openFile(string PathName);
	void writeFile(string DATA);
	void closeFile();
	void showTree(string path, size_t deep);
	void dump(string fname);
	~VFS() {
		for(vfsunit* &x : files)
			delete x;
	}
}vfs;

class file : public vfsunit {
	public:
	file(string Path, string Name, string Content, char Mod) : vfsunit(Path, Name, Content, Mod, 0) {};
	file(const vfsunit& O) : vfsunit(O) {};
	string getContent();
	void setContent(string Content);
};

class directory : public vfsunit {
	public:
	directory(string Path, string Name, string Content, char Mod) : vfsunit(Path, Name, Content, Mod, 1) {};
	directory(const vfsunit& O) : vfsunit(O) {};
	string getContent();
	void setContent(string Content);
};

class link : public vfsunit {
	vfsunit &ln;
	public:
	link(string Path, string Name, string Content, char Mod) : vfsunit(Path, Name, Content, Mod, 2), ln(vfs.getFile(Content)) {};
	link(const vfsunit& O) : vfsunit(O), ln(vfs.getFile(content)) {};
	string getContent();
	void setContent(string Content);
};


////////////////////////////////////////////	
string vfsunit::getName() {
	return name;
}

void vfsunit::setName(string Name) {
	name = Name;
}

string vfsunit::getPath() {
	return path;
}
	
char vfsunit::getMod() {
	return mod;
}

void vfsunit::setMod(char Mod) {
	mod = Mod;
}

char vfsunit::getType() {
	return type;
}
////////////////////////////////////////////	

string file::getContent() {
	if(!(mod&1))
		throw accessDeniedException();
	return content;
}

void file::setContent(string Content) {
	if(!(mod&2))
		throw accessDeniedException();
	content = Content;
}

////////////////////////////////////////////


string directory::getContent() {
	throw directoryChangeException();
	return path;
}

void directory::setContent(string Content) {
	throw directoryChangeException();
}
////////////////////////////////////////////



string link::getContent() {
	if(!(mod&1))
		throw accessDeniedException();
	return content;
}

void link::setContent(string Content) {
	if(!(mod&2))
		throw accessDeniedException();
	ln = vfs.getFile(Content);
	content = Content;
}

////////////////////////////////////////////////




vfsunit& VFS::getFile(string PathName) {
	for(vfsunit* &x : files) 
		if(x->getPath() + x->getName() == PathName)
			return *x;
	throw fileNotFoundException();
}

void VFS::addFile(string PathName, string Content, char Mod, char type) {
	try {
		getFile(PathName);
	}
	catch(fileNotFoundException e) {
		size_t i = PathName.find_last_of('/');
		checkDirectory(PathName.substr(0, i+1), 2);
		switch(type) {

			case 0:
			files.push_back(new file(PathName.substr(0, i+1), PathName.substr(i+1), Content, Mod));
			break;
				
			case 1:
			files.push_back(new directory(PathName.substr(0, i+1), PathName.substr(i+1), Content, Mod));
			break;
				
			case 2:
			files.push_back(new link(PathName.substr(0, i+1), PathName.substr(i+1), Content, Mod));
			break;
				
			default:
			throw logic_error("Unknown vfsunit type!");
		}
		sort(files.begin(), files.end());
		return;
	};
	throw fileExistsException();
}




vector<string> VFS::getFiles(string path) {
	checkDirectory(path, 1);
	vector<string> res;
	for(vfsunit* &x: files)
		if(x->getPath()==path)
			res.push_back(x->getName());
	return res;
}

void VFS::checkDirectory(string path, char mod) {
	if(path=="/")
		return;
	try {			
		vfsunit &dir = getFile(path.substr(0,path.length()-1));
		if(dir.getType()!=1)
			throw directoryIsFileException();
		if(!(dir.getMod()&mod))
			throw accessDeniedException();
	}
	catch(fileNotFoundException e) {
		throw filePathIncorrectException();
	}
	
}

void VFS::deleteFile(string PathName) {
	vfsunit &f = getFile(PathName);
	try {
		checkDirectory(PathName+"/",2);
	}
	catch(directoryIsFileException e) {
		for(vector<vfsunit*>::iterator x=files.begin(); x!=files.end(); x++) 
			if((*x)->getPath() + (*x)->getName() == PathName) {
				files.erase(x);
				break;
			}
		return;
	}
	throw directoryRemoveException();
}

void VFS::deleteRecursive(string PathName) {
	vfsunit &f = getFile(PathName);
	try {
		checkDirectory(PathName+"/",2);
	}
	catch(directoryIsFileException e) {
		for(vector<vfsunit*>::iterator x=files.begin(); x!=files.end(); x++) 
			if((*x)->getPath() + (*x)->getName() == PathName) {
				files.erase(x);
				break;
			}
		return;
	}
	vector<string> fs = getFiles(PathName+"/");
	for(string &x : fs)
		deleteRecursive(PathName + "/" + x);
	for(vector<vfsunit*>::iterator x=files.begin(); x!=files.end(); x++) 
		if((*x)->getPath() + (*x)->getName() == PathName) {
			files.erase(x);
			break;
		}
}

void VFS::deleteFileSu(string PathName) {
	vfsunit &f = getFile(PathName);
	try {
		checkDirectory(PathName+"/",255);
	}
	catch(directoryIsFileException e)
	{
		for(vector<vfsunit*>::iterator x=files.begin(); x!=files.end(); x++) 
			if((*x)->getPath() + (*x)->getName() == PathName) {
				files.erase(x);
				break;
			}
		return;
	}
	throw directoryRemoveException();
}


void VFS::openFile(string PathName) {
	if(lock!=nullptr)
		throw fileNotClosedException();
	lock = &getFile(PathName);
	lockmod = lock->getMod();
	if(!(lockmod&2)) {
		lock = nullptr;
		throw accessDeniedException();
	}
	lock->setMod(4);
}

void VFS::writeFile(string DATA) {
	if(lock==nullptr)
		throw fileNotOpenedException();
	lock->setMod(lockmod);
	lock->setContent(DATA);	
	lock->setMod(4);
}
void VFS::closeFile() {
	lock->setMod(lockmod);
	lock = nullptr;
}

void VFS::copyFile(string PathName, string NewPath) {
	vfsunit &f = getFile(PathName);
	try {
		getFile(NewPath);
	}
	catch(fileNotFoundException e) {
		addFile(NewPath, f.getContent(), f.getMod(), f.getType());
		return; 
	}
	throw fileExistsException();
}

void VFS::copyFiles(string Path, string NewPath) {
	vfsunit &f = getFile(Path);
	try {
		getFile(NewPath);
	}
	catch(fileNotFoundException e) {
		try {
			checkDirectory(Path+"/", 1);
		}
		catch(directoryIsFileException e) {
			addFile(NewPath, f.getContent(), f.getMod(), f.getType());
			return;
		}
		catch(accessDeniedException e) {
			return;
		}
		addFile(NewPath, "", f.getMod(), f.getType());
		vector<string> files = vfs.getFiles(Path+"/");
		for(string &x : files)
			copyFiles(Path + "/" + x, NewPath + "/" + x);
		return; 
	}
	throw fileExistsException();
}

vector<string> VFS::findFile(string name) {
	vector<string> res;
	for(vfsunit* &x: files)
		if(x->getName()==name)
			res.push_back(x->getPath()+x->getName());
	return res;
}


void VFS::showTree(string path, size_t deep) {
	if(deep==0)
		cout << path << endl;
		
	vector<string> fs = getFiles(path);
	for(string &x : fs) {
		for(size_t i=0; i<deep; i++)
			cout << " ";
		cout << x << endl;
		try {
			checkDirectory(path+x+"/", 1);
		}
		catch(directoryIsFileException e) {
			continue;
		}
		catch(accessDeniedException e) {
			continue;
		}
		showTree(path+x+"/", deep+1);
	}
}

//JSON rules :D
void VFS::dump(string fname) {
	ofstream of(fname);
	if(!of.is_open())
		throw dumpUnsuccessfulException ();
	of	<< "[" << endl;
	for(size_t i=0; i<files.size(); i++) {
		of 	<< "\t{" << endl 
				<< "\t\t\"path\": " << "\"" << files[i]->getPath() << "\"," << endl
				<< "\t\t\"name\": " << "\"" << files[i]->getName() << "\"," << endl
				<< "\t\t\"content\": " << "\"";
		try {
			of << files[i]->getContent();
		}
		catch(directoryChangeException e) {}
		of 	<< "\"," << endl
				<< "\t\t\"name\": " << (int)files[i]->getMod() << "," << endl
				<< "\t\t\"type\": " << (int)files[i]->getType() << endl
				<< "\t}" << (i+1==files.size() ? "" : ",") << endl;
	}			
	of << "]" << endl ;
	of.close();
}

////////////////////////////////////////////	

int main() {
	
	string Path = "/";
	string command;
	char buffer[1024];
	while(1) {
		cout << "shell@localhost " << Path << "$";
		cin.getline(buffer, 1024);
		stringstream sin(buffer);
		sin >> command;
		try {
			if(command == "CREATE") {
				sin >> command;
				char t;
				if(command == "FILE") 
					t = 0;
				else if(command == "DIR")
					t = 1;
				else if(command == "LINK") 
					t = 2;
				else {
					cout << "Usage: CREATE FILE/DIR/LINK [filename] (linkpath)" << endl;
					continue;
				}
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				if(t==2) {
					string path;
					sin >> path;
					if(path[0]!='/')
						path = Path + path;
					vfs.addFile(command, path, 3, t);
				}
				else
					vfs.addFile(command, "", 3, t);
			}
			else if((command == "LIST")||(command == "list")) {
				vector<string> files= vfs.getFiles(Path);
				for(string &x : files)
					cout << x << endl;
			}
			else if(command == "RWC") {
				sin >> command;
				if(command == "OPEN") {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfs.openFile(command);
				}
				else if(command == "WRITE") {
					char line[256];
					sin.get();
					sin.getline(line, 256);
					vfs.writeFile(string(line));
				}
				else if(command == "CLOSE") 
					vfs.closeFile();
				else
					cout 	<< "Usage: RWC OPEN [filename]" << endl
							<< "       RWC WRITE [data]" << endl
							<< "       RWC CLOSE" << endl;
			}
			else if(command == "SYMA"){
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfsunit &f = vfs.getFile(command);
				if(f.getType()!=2)
					cout << "File isn't symbolic link" << endl;
				else 
					cout << f.getContent() << endl;
			}
			else if((command == "CHMOD")||(command == "chmod")) {
				string mod;
				sin >> mod >> command;
				if(command[0]!='/')
					command = Path + command;
				vfsunit &f = vfs.getFile(command);
				if(mod=="n")
					f.setMod(0);
				else if(mod=="r")
					f.setMod(1);
				else if(mod=="w")
					f.setMod(2);
				else if((mod=="rw")||(mod=="wr"))
					f.setMod(3);
				else
					cout << "Usage: CHMOD n/r/w/rw [file]" << endl;
			}
			else if((command == "RM")||(command == "rm")) {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfs.deleteFile(command);
			}
			else if((command == "SRM")||(command == "su_rm")) {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfs.deleteFileSu(command);
			}
			else if(command == "CAT") {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				cout << vfs.getFile(command).getContent() << endl;
			}
			else if(command == "CP") {
				string copy;
				sin >> command >> copy;
				if(command[0]!='/')
					command = Path + command;
				if(copy[0]!='/')
					copy = Path + copy;
				vfs.copyFile(command, copy);
			}
			else if((command == "FINDR")||(command == "find_r")) {
				sin >> command;
				vector<string> files = vfs.findFile(command);
				for(string &x : files)
					cout << x << endl;
				if(files.size()==0)
					throw fileNotFoundException();
			}
			else if((command == "CPR")||(command == "cp_r")) {
				string copy;
				sin >> command >> copy;
				if(command[0]!='/')
					command = Path + command;
				if(copy[0]!='/')
					copy = Path + copy;
				vfs.copyFiles(command, copy);
			}
			else if((command == "LSR")||(command == "list_r")) {
				vfs.showTree(Path, 0);
			}
			else if(command == "DUMP") {
				sin >> command;
				vfs.dump(command+".json");
			}
			else if(command == "cd") {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfs.checkDirectory(command, 1);
				Path = command;
			}
			else if(command == "mkdir") {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfs.addFile(command, "", 3, 1);
			}
			else if(command == "touch") {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfs.addFile(command, "", 3, 0);
			}
			else if(command == "ln") {
				string path;
				sin >> path >> command;
				if(command[0]!='/')
					command = Path + command;
				if(path[0]!='/')
					path = Path + path;
				vfs.addFile(command, path, 3, 2);
			}
			else if(command == "open") {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfs.openFile(command);
			}
			else if(command == "write") {
				char line[256];
				sin.get();
				sin.getline(line, 256);
				vfs.writeFile(string(line));
			}
			else if(command == "close") 
				vfs.closeFile();
			else if(command == "find") {
				sin >> command;
				vector<string> files = vfs.getFiles(Path);
				for(string &x : files)
					if(x==command) {
						cout << Path + command;
						break;
					}
				if(files.size()==0)
					throw fileNotFoundException();
			}
			else if(command == "rm_r") {
				sin >> command;
				if(command[0]!='/')
					command = Path + command;
				vfs.deleteRecursive(command);
			}
			else if((command == "EXIT")||(command == "exit")) 
				break;
		}
		catch(accessDeniedException e) {
			cout << "Access denied" << endl;
		}
		catch(directoryChangeException e) {
			cout << "You can't read or write directory" << endl;
		}
		catch(fileNotFoundException e) {
			cout << "File not found" << endl;
		}	
		catch(fileExistsException e) {
			cout << "File already exists" << endl;
		}
		catch(filePathIncorrectException e) {
			cout << "Path isn't correct" << endl;
		}
		catch(directoryIsFileException e) {
			cout << "You can't use file as directory" << endl;
		}
		catch(fileNotOpenedException e) {
			cout << "You can't write in file while file isn't opened" << endl;
		}
		catch(fileNotClosedException e) {
			cout << "You can't open new file while previous isn't closed" << endl;
		}
		catch(dumpUnsuccessfulException e) {
			cout << "File can't be opened for writing" << endl;
		}
		catch(directoryRemoveException e) {
			cout << "Directory can't be deleted by rm" << endl;
		}
	}
	return 0;
}