#include <iostream>
#include <string>
#include <vector>

using namespace std;


class FileContent{
	int content;
	
	public:
		FileContent(){
			content = 0;
		}
		
		~FileContent(){
		}
};

class SFile:protected FileContent{

	public:
		string name;
		
		SFile(string str){
			name = str;
			FileContent();
		}
		
};

class Directory{

	vector<SFile*> FArr;
	vector<Directory*> DArr;
	
	public:
		string dName;
		
		Directory(string str){
			dName = str;
		}
		
		void CreateDirectory(string name){
			Directory* dptr = new Directory(name);
			DArr.push_back(dptr);
		}
		
		void CreateFile(string fname){
			SFile* fptr = new SFile(fname);
			FArr.push_back(fptr);
		}
			
		int FindDirectory(string target){
			int i = 0;
			while (DArr[i]->dName != target) i++;
			return i;
		}
				
		int FindFile(string target){
			int i = 0;
			while (FArr[i]->name != target) ++i;
			return i; 
		}
		
		void DeleteFile(string fname){
			int index = FindFile(fname);
			delete FArr[index];
			FArr.erase(FArr.begin() + index);
			
		}
		
		void DeleteDirectory(string name){
			int index = FindDirectory(name);
			delete DArr[index];
			DArr.erase(DArr.begin() + index);
		}

		void RM(string way);
		Directory* operator/ (string name);
				
		~Directory(){
				
		}
};

Directory* Directory::operator/ (string name){
	return DArr[FindDirectory(name)];
}

void Directory::RM(string way){
	
	int number = 0;
	for (int i = 0; i < way.size(); i++){
		if (way[i] == '/') number++;
	}
		
	if (number){
			
	int i = 0;
	string str;
	string newway;
	
	while (way[i] != '/'){
		str += way[i];
		i++;
	}
				
	int Next = FindDirectory(str);
				
	for (int j = i + 1; j < way.size(); j++)
		newway += way[j];
	
	DArr[Next]->RM(newway);
	}
			
	if (number == 0) {
		int index = FindFile(way);
		delete FArr[index];
		FArr.erase(FArr.begin() + index);	
	}		
}


int main(){
	
	Directory First("First");
	
	First.CreateFile("MyFile");
	First.CreateDirectory("Second");
	(First/"Second") -> CreateFile("MyFile2");
	First.RM("Second/MyFile2");
	First.RM("MyFile");


	return 0;
}
