#include "CsvFile.h"
#include "IFile.h"

CsvFile::CsvFile(const std::string filePath, const std::string mode)
{
	this->filePath = filePath;

	if (mode.find("r") != std::string::npos) openMode |= std::fstream::in; // do odczytu,
	if (mode.find("w") != std::string::npos) openMode |= std::fstream::out; // do zapisu,
	if (mode.find("a") != std::string::npos) openMode |= std::fstream::app; // wszystkie operacje dzieja sie na koncu pliku, 
	if (mode.find("t") != std::string::npos) openMode |= std::fstream::trunc; // wszystko co bylo w pliku przed plikiem, jest czyszczone,
	if (mode.find("e") != std::string::npos) openMode |= std::fstream::ate; // wskaznik odczytu/zapisu na koniec pliku,

	file.open(filePath, openMode);		// otwarcie wraz z typem,
	file.seekg(0, std::fstream::end);	//
	length = file.tellg();				// odczytanie dlugosci pliku,
	file.seekg(0, std::fstream::beg);	//
}



void CsvFile::WriteLine(Point v)
{
	file.seekp(0, std::fstream::end);
	file << v.x << ',' << v.y << ',' << v.z << std::endl;
}

std::vector<std::string> CsvFile::Split(const std::string str, char delim) {
	
	std::vector<std::string> result;
	std::stringstream ss(str);			//pobranie strumienia lancucha,
	std::string item;					// pusty string,
	while (getline(ss, item, delim)) {	// bierzemy strumien (ss), wsadzamy do lancucha (item) pomijajac dany char (delim),
		result.push_back(item);			// wsadzamy lancuch (item) do wektora,
	}
	return result;
}



IFile::FileError CsvFile::Write(const std::vector<Point>& v)
{
	FileError retVal = FileError(FileError::ACCESS_DENIED);

	if (openMode & std::fstream::out)
	{
		file.seekp(0, std::fstream::end);
		for (unsigned int i = 0; i < v.size(); i++)
		{
			file << v[i].x << ',' << v[i].y << ',' << v[i].z << std::endl;
		}
		length = file.tellp();

		retVal = FileError(FileError::SUCCESS);
	}

	return retVal;
	
}

IFile::FileError CsvFile::Read(std::vector<Point>& v)
{
	FileError retVal = FileError(FileError::ACCESS_DENIED);

	if (openMode & std::fstream::in)
	{
		while (file.tellp() < length - 2)
		{
			std::string pom;
			file >> pom;
			std::vector<std::string> pomV;
			pomV = Split(pom, ',');

			v.push_back(Point{ std::stod(pomV[0]),std::stod(pomV[1]),std::stod(pomV[2]) });
		}

		retVal = FileError(FileError::SUCCESS);
	}

	return retVal;
}

IFile::FileError CsvFile::Read(Point& p, const unsigned long idx)
{
	FileError retVal = FileError(FileError::ACCESS_DENIED);


	if (idx * sizeof(Point) > length)
	{
		retVal = FileError(FileError::OUT_OF_BOUNDS);
	}

	else if (openMode & std::fstream::in)
	{
		file.seekg(0, std::fstream::beg);

		for (unsigned long i = 0; i < idx; i++)
		{
			file.ignore(1000, '\n');
		}
		std::string pom;
		file >> pom;

		std::vector<std::string> pomV = Split(pom, ',');

		p = Point{ std::stod(pomV[0]),std::stod(pomV[1]),std::stod(pomV[2]) };

		retVal = FileError(FileError::SUCCESS);
	}

	return retVal;
}
