#pragma once
#include "filesystemelement.h"
#include "MyFolder.h"
#include <memory>

class MyFile :
	public FileSystemElement, public enable_shared_from_this<MyFile>
{
private:
	string data;
public:
	MyFile(shared_ptr<MyFolder> parent = shared_ptr<MyFolder>(nullptr), string name = "blank_file", string data = "default_data");
	~MyFile(void);

	friend ostream& operator<<(ostream& out_stream, const MyFile& rhs);
};

