#include "Header.h"
using namespace std;

Link::Link(string name) :FileSys(nullptr, name, "link") { ; }

Link::Link(FileSys * fs, string name, FileSys * lnk) : FileSys(fs, name, "link") {link = lnk; }

FileSys * Link::getLink(){
	return link;
}


