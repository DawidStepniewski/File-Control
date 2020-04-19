#include "BinaryFile.h"

BinaryFile::BinaryFile(const std::string filePath, const std::string mode) 
{
	this->filePath = filePath;
	openMode = std::fstream::binary;

	if (mode.find("r") != std::string::npos) openMode |= std::fstream::in; // do odczytu
	if (mode.find("w") != std::string::npos) openMode |= std::fstream::out; // do zapisu
	if (mode.find("a") != std::string::npos) openMode |= std::fstream::app; // wszystkie operacje dzieja sie na koncu pliku, 
	if (mode.find("t") != std::string::npos) openMode |= std::fstream::trunc; // wszystko co bylo w pliku przed plikiem, jest czyszczone
	if (mode.find("e") != std::string::npos) openMode |= std::fstream::ate; // wskaznik odczytu/zapisu na koniec pliku

	file.open(filePath, openMode);		
	file.seekg(0, std::fstream::end);	//
	length = file.tellg();				// odczytanie dlugosci pliku 
	file.seekg(0, std::fstream::beg);	//
}



IFile::FileError BinaryFile::Write(const std::vector<Point>& v)
{
	FileError retVal = FileError(FileError::ACCESS_DENIED);

	if (openMode & std::fstream::out)
	{
		file.write((const char*)v.data(), v.size() * sizeof(Point));
		retVal = FileError(FileError::SUCCESS);
	}

	return retVal;
}

IFile::FileError BinaryFile::Read(std::vector<Point>& v)
{
	FileError retVal = FileError(FileError::ACCESS_DENIED);

	if (openMode & std::fstream::in)
	{
		v.clear();							// usuwa wszystkie elementy z wektora
		v.resize(length / sizeof(Point));	// zmienia rozmiar pliku na "sizeof(Point)"
		file.seekg(0, std::fstream::beg);	// ustawia pozycje poczatku strumienia na 0
		file.read((char*)v.data(), length); // zczytanie zawartosci pliku
		retVal = FileError(FileError::SUCCESS);
	}

	return retVal;
}

IFile::FileError BinaryFile::Read(Point& p, const unsigned long idx)
{
	FileError retVal = FileError(FileError::ACCESS_DENIED);

	if (idx * sizeof(Point) > length)
	{
		retVal = FileError(FileError::OUT_OF_BOUNDS);
	}
	else if (openMode & std::fstream::in)
	{
		file.seekg(idx * sizeof(Point));
		file.read((char*)(&p), sizeof(Point));
		retVal = FileError(FileError::SUCCESS);
	}

	return retVal;
}