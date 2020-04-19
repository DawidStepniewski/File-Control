#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include "Point.h"

class IFile
{
protected:
	std::fstream file;
	std::string filePath;
	unsigned long length;
	std::fstream::openmode openMode;
public:
	IFile(const std::string, const std::string);
	IFile();
	virtual ~IFile()
	{
		file.close();
	}

	enum class FileError
	{
		SUCCESS,
		ACCESS_DENIED,
		OUT_OF_BOUNDS,
		FILE_INVALID
	};

	virtual FileError Write(const std::vector<Point>&) = 0;
	virtual FileError Read(std::vector<Point>&) = 0;
	virtual FileError Read(Point&, const unsigned long) = 0;
};
