#include "Header.h"

std::vector<std::string>  split(std::string str, std::string splt) {
	int i, k, j;
	std::vector<std::string> v;
	i = str.find(splt);
	j = i;
	//cout << "i is: " << i << endl;
	if (i == -1 && str.size() != 0) { v.push_back(str.substr(0, str.size())); return v;}
	else if (i == -1 && str.size() == 0) return v;
	else if (i) {
		v.push_back(str.substr(0, i));

	}

	while (true) {

		i = str.find(splt, j + splt.length());

		if (i == -1 && v.size() > 1) {
			k = j;
			if (str.length() - k > 0) { v.push_back(str.substr(k + 1, k - str.length())); }
			break;
		}
		else if (i == -1) {
			if (str.size() > v.at(0).size()) {
				//cout << "str size: " << str.size() << endl;
				//cout << "v size: " << v.at(0).size() << endl;
				//cout << v.at(0) << endl;
				v.push_back(str.substr(j+1, str.size() - 1));
			}
			//cout << "else if block" << endl;
			break;
		}
		v.push_back(str.substr(j + splt.length(), i-1 - j));
		j = i;
		//k = i;
	}
	return v;
}




Link * Find(string name, vector<Link*> v){
	for(int i(0); i<v.size(); i++){
		if(name == v.at(i)->getName()){return v.at(i);}
	}
}
