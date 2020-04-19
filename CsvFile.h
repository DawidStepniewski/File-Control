#pragma once
#include <fstream>
#include <vector>
#include "Point.h"
#include "BinaryFile.h"
#include "FileError.h"
#include <sstream>
#include "IFile.h"

class CsvFile : public IFile
{
	void WriteLine(Point);
	std::vector<std::string> Split(const std::string, char);
	
public:
	CsvFile(const std::string, const std::string);



	virtual FileError Write(const std::vector<Point>&);
	virtual FileError Read(std::vector<Point>&);
	virtual FileError Read(Point&, const unsigned long);
};
