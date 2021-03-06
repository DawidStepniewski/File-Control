#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
#include "FileError.h"
#include "IFile.h"

class BinaryFile : public IFile
{

public:
	BinaryFile(const std::string, const std::string);
	
	

	virtual FileError Write(const std::vector<Point>&);
	virtual FileError Read(std::vector<Point>&);
	virtual FileError Read(Point&, const unsigned long);
};

