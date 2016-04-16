// laba 5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fl.h"
#include "folder.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string n; int a; string n1; 
	vector<file> g; folder t;
	cout<<"vvodite cmd"<<endl;
	string cmd; cin>>cmd;
	while(cmd != "end")
	{
	if(cmd=="createfile")
	 {
       cout<<"name:  ";
	   cin>>n;
	   cout<<"a:  ";
	   cin>>a;
	   file f(n, a);
	   g.push_back(f);
	 }
	else
	  if(cmd=="createfolder")
	  {
		 cout<<"name of folder:  ";
		 cin>>n1;
		 t.set_name(n1);
	  }
    else
	 if(cmd=="putonfolder")
	 {
		 cout<<"name of file? ";
		 cin>>n1;
		 for(int i=0; i<g.size(); i++)
			 if(g[i].get_file()==n1)
				 t.addf(g[i]);
	 }
	 else
		if(cmd=="getint")
		{
			cout<<"name of file: ";
			cin>>n1;
			for(int i=0; i<t.get_size(); i++)
				if(t(i).get_file()==n1)
				  cout<<t(i).get_int()<<endl;
		}
	cin>>cmd;
	}
	system("pause");
	return 0;
}

