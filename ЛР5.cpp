#include <iostream>
#include <string>
#include <vector>



class Error{
		std::string inf;
	
	public: 
		Error(std::string str){
	 		inf = str;
		}
		what(){
			std::cout << inf << '\n';
		} 
		~Error(){
		}
};


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
		std::string fName;
		
		SFile(std::string str){
			fName = str;
			FileContent();
		}
		~SFile(){
		}
};

class Directory{

	std::vector<SFile*> FArr;
	std::vector<Directory*> DArr;
	
	public:
		std::string dName;
		
		Directory(std::string str){
			dName = str;
		}
		
		void CreateDirectory(std::string name){
			Directory* dptr = new Directory(name);
			DArr.push_back(dptr);
		}
		
		void CreateFile(std::string fname){
			SFile* fptr = new SFile(fname);
			FArr.push_back(fptr);
		}
			
		int FindDirectory(std::string target){
			int i = 0;
			while (DArr[i]->dName != target && i < DArr.size()) i++;
			
			if (DArr[i]->dName != target) 
				throw Error("There is no such Directory");
			return i;
		}
				
		int FindFile(std::string target){
			int i = 0;
			while (FArr[i]->fName != target && i < FArr.size()) ++i;
			
			if (FArr[i]->fName != target) 
				throw Error("There is no such File");
			return i; 
		}
		
		void DeleteFile(std::string fname){
			int index = FindFile(fname);
			delete FArr[index];
			FArr.erase(FArr.begin() + index);
			
		}
		
		void DeleteDirectory(std::string name){
			int index = FindDirectory(name);
			delete DArr[index];
			DArr.erase(DArr.begin() + index);
		}

		void RM(std::string way);
		void ShowList();
		Directory* operator/ (std::string name);
				
		~Directory(){
				
		}
};

Directory* Directory::operator/ (std::string name){
	return DArr[FindDirectory(name)];
}

void Directory::RM(std::string way){
	
	int number = 0;
	for (int i = 0; i < way.size(); i++){
		if (way[i] == '/') number++;
	}
		
	if (number){
			
	int i = 0;
	std::string str;
	std::string newway;
	
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

void Directory::ShowList(){
	
	std::cout << '/' << this->dName << std::endl;
	if (FArr.size()) std::cout << "  Files:" << std::endl;
	for (int i = 0; i < FArr.size(); i++){
		std::cout << "   " << FArr[i]->fName << std::endl;
	}
	
	if (DArr.size()) std::cout << "Directory:" << std::endl;
	for (int i = 0; i < DArr.size(); i++){
		DArr[i]->ShowList();
	}

}


int main(){
	try{

	Directory First("First");
	First.CreateFile("MyFile");
	First.CreateFile("MyNewFile");
	First.CreateDirectory("Second");
	(First/"Second") -> CreateFile("MyFile2");
	(First/"Second") -> CreateDirectory("Third");
	
	First.ShowList();
	First.RM("Second/MyFile2");
	First.RM("MyNewFile");
	
	//First.FindFile("MyFile78");
	std::cout << std::endl;
	First.ShowList();
	} catch(Error& e){
		e.what();
	}

	return 0;
}
