//Сычев Роман ИУ8-24
//27 вариант
//
#include "stdafx.h" 
using namespace std; 
class Directoryclass; 
class Fileclass
{ 
protected: 
string Name; 
string Data; 
public: 
friend Directoryclass; 
Fileclass(string n, string d=0) 
{ 
int q = n.length(); 
n += ".f"; 
Name = n; 
Data = d; 
} 
}; 
class Directoryclass 
{ 
protected: 
Directoryclass* pDir[10]; 
Fileclass* pFileclass[10]; 
string Name; 
public: 
Directoryclass* rod; 
Directoryclass(string n) 
{ 
Name = n; 
for (int i = 0;i < 10;i++) 
{ 
pDir[i] = nullptr; 
pFileclass[i] = nullptr; 
} 
} 
void created(string n) 
{ 
Directoryclass* pnew = new Directoryclass(n); 
int i = 0; 
while (pDir[i] != 0) 
{ 
i++; 
} 
pDir[i] = pnew; 
pnew->rod = this; 
} 
void createf(string n,string d) 
{ 
Fileclass* pnew = new Fileclass(n,d); 
int i = 0; 
while (pFileclass[i] != 0) 
{ 
i++; 
} 
pFileclass[i] = pnew; 
} 
void remove(string n) 
{ 
for (int i = 0;i < 10;i++) 
{ 
if(pDir[i]->Name == n) pDir[i]=nullptr; 
if(pFileclass[i]->Name == n) pFileclass[i] = nullptr; 
} 
} 
void list() 
{ 
int i = 0; 
cout << "Directories:" << endl; 
while (pDir[i] != 0) 
{ 
cout << pDir[i]->Name<<endl; 
i++; 
} 
i = 0; 
cout << "Files:" << endl; 
while (pFileclass[i] != 0) 
{ 
cout << pFileclass[i]->Name<<endl; 
i++; 
} 
} 
void print() 
{ 
cout << Name << ">>"; 
} 
void open(string n) 
{ 
int i = 0; 
while (pFileclass[i]->Name != n) 
{ 
i++; 
} 
cout << pFileclass[i]->Data<<endl; 
} 
friend void cd(string n); 
}; 



Directoryclass headdir("main"); 
Directoryclass* CurDirection=&headdir; 
void cd(string n) 
{ 
int i = 0; 
while (CurDirection->pDir[i]->Name != n) 
{ 
i++; 
} 
CurDirection = CurDirection->pDir[i]; 
} 
//cd, mkdir, open, list, 
int main() 
{ 
string Data, value,text; 
while (Data != "exit") 
{ 
CurDirection->print(); 
cin >> Data; 
switch (Data[0]) 
{ 
case 'c'://cd 
cin >> value; 
cd(value); 
break; 
case't'://cr Fileclasse 
cin >> value >> text; 
CurDirection->createf(value, text); 
break; 
case 'm'://cr dir 
cin >> value; 
CurDirection->created(value); 
break; 
case 'l'://list 
CurDirection->list(); 
break; 
case '.'://back 
CurDirection = CurDirection->rod; 
break; 
case'o'://open 
cin >> value; 
CurDirection->open(value); 
break; 
default: 
cout << "Wrong Command"<<endl; 
break; 
} 

} 

return 0; 
}
