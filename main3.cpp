#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;
class Directory;
class File {
private:
    string mName;
    int nContent;
    
public:
    File(){
        nContent = 0;
        mName = "";
    }
    
    void set_param(string s, int c){
        mName = s;
        nContent = c;
    }
    
    string name(){
        return mName;
    }
  
    int content(){
        return nContent;
    }
    
    ~File(){}
};

class Label {
    
private:
    string name;
    
    File *ptrf;
    
public:
    Label(){
        
    }
    Label(string s, File* f){
        name = s+"_label";
        ptrf = f;
    }
    
    string namel(){
        return name;
    }
    File* f(){
        return ptrf;
    }
    
    friend class Directory;
};

class Directory{
    
private:
    string name_d;
    vector <File> f;
    vector <Label> label;
    Directory *prev, *next;
    
    int find(string c){
        int p=0;
        int d=0;
        for (int i = 0; i < f.size(); i++)
        {
            if (f[i].name() == c) return i;
            else p=-1;
            
        }
        for (int i = 0; i < label.size(); i++)
        {
            if (label[i].namel() == c) return i;
            else d=-1;
        }
        if (d==-1)
        {
            throw invalid_argument("the name of file wasn't found");
            
        }
        if (p==-1)
        {
            throw invalid_argument("the name of file wasn't found");

        }
        return -1;
    }
    
public:
    Directory() {
        name_d = "";
        
    }
    Directory(string c){
        name_d = c;
    }
    Directory(string c, Directory *prevv){
        name_d = c;
        prev = prevv;
    }
    
    void create_nextptr(Directory *nextt){
        next = nextt;
    }
    
    void show_files(){
        for (int i = 0; i < f.size(); i++){
            cout << f[i].name() << endl;
        }
        for (int i = 0; i < label.size(); i++){
            cout << label[i].namel() << endl;
        }
    }
    
    
    void open_file(string s){
        try{
        cout << f[find(s)].content() << endl;
        }
        catch(exception &e){
            cout<<e.what();
        }catch(...) {
            cout<<"unknown exception"<<endl;
        }
    }
    void open_label(string s){
        File*  f;
        try{
        f = label[find(s)].ptrf;
        f->content();
        }
        catch(exception &e){
            cout<<e.what();
        }catch(...) {
            cout<<"unknown exception"<<endl;
        }
    }
    
    void create_file(string s, int c = 0){
        File a;
        a.set_param(s, c);
        f.push_back(a);
    }
    
    void create_label(string s, File* f){
        label.push_back(Label(s, f));
        
    }
    
    string d_name(){
        return name_d;
    }
    
    void record(string s, int c){
      
        f[find(s)].set_param(s, c);
        
    }
    
    File* return_ptr(string s){
        return &f[find(s)];
    }
    
    void delete_file(string s){
     
            // f = {1, 2, 3, 4, 5};
            // S = 2
        f.erase(f.begin() + find(s)); // f = {1, 3, 4, 5};
//        vector<File> f_copy(f); // f_copy = {1, 3, 4, 5};
//        f_copy.swap(f); // f = f_copy && f_copy = f
    }
    
};

//int find_d(vector<Directory>, string);
int find_d(vector<Directory> d, string s){
    int p=0;
    for (int i = 0; i < d.size(); i++){
        if (d[i].d_name() == s) return i;
        else p=-1;
    }
    if (p==-1)
    {
        throw invalid_argument("the name of dir wasn't found");
        
    }
    return 0;
}

int main()
{
    vector<Directory>dir;
    {
        dir.push_back(Directory("C", 0));
    }
    string s;
    string copy = " copy";
    string name;
    int content;
    
    int ii = 0;
    
    do
    {
        cin >> s;
        if (s == "touch") {
            cout << "enter file name to create: " << endl;
            
            cin >> name;
            dir[ii].create_file(name);
        }
        if (s == "list"){
            dir[ii].show_files();
        }
        if (s == "copy"){
            try{
            cout << "name of file to copy:" << endl; cin >> name;
            name += " copy";
            dir[ii].create_file(name);
            }
            catch(exception &e){
                cout<<e.what();
            }catch(...) {
                cout<<"unknown exception"<<endl;
            }
        }
        if (s == "touchl"){
            
            try {
            cout << "name of file to create yarlyk"; cin >> name;
            dir[ii].create_label(name, dir[ii].return_ptr(name));
            }
            catch(exception &e){
                cout<<e.what();
            }catch(...) {
                cout<<"unknown exception"<<endl;
            }
        }
        if (s == "open"){
            try {
            cout << "enter name of file to open " << endl;
            cin >> name;
            
            if (name.find("_label") != -1){
                dir[ii].open_label(name);
                
            }
            
            dir[ii].open_file(name);
            }
            catch(exception &e){
                cout<<e.what();
            }catch(...) {
                cout<<"unknown exception"<<endl;
            }
        }
        if (s == "write"){
            try {
            cout << "name of file to write: ";
            cin >> name;
            cout << "enter new content: ";
            cin >> content;
            dir[ii].record(name, content);
            }
            catch(exception &e){
                cout<<e.what();
            }catch(...) {
                cout<<"unknown exception"<<endl;
            }
            
        }
        f (s == "rm"){
            try {
            cout << " file to remove:";
            cin >> name;
            dir[ii].delete_file(name);
            }
            catch(exception &e){
                cout<<e.what();
            }catch(...) {
                cout<<"unknown exception"<<endl;
            }
        }
        if (s == "newd"){
            cout << "name of dir to create:"; cin >> name;
            
            dir.push_back(Directory(name, &dir[ii]));
            dir[ii].create_nextptr(&dir[ii + 1]);
        }
        
        if (s == "godir"){
            try {
            cout << " dir name to go:"; cin >> name;
            ii = find_d(dir, name);
            }
            catch(exception &e){
                cout<<e.what();
            }catch(...) {
                cout<<"unknown exception"<<endl;
            }
        }
        if (s == "listdir"){
            for (int i = 0; i < dir.size(); i++){
                cout << dir[i].d_name() << endl;
            }
        }
        if (s == "deldir"){
            try {
            cout << "dir to remove:"; cin >> name;
            
            dir.erase(dir.begin() + find_d(dir, name));
            vector<Directory>(dir).swap(dir);
            cout << "deleted";
            }
            catch(exception &e){
                cout<<e.what();
            }catch(...) {
                cout<<"unknown exception"<<endl;
            }
        }
    cout << "--------------------------" << endl;
    } while (s != "`");
    return 0;
}

