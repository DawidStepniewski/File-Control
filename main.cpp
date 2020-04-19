#include <iostream>
#include <ostream>
#include "FileFactory.h"
#include "main.h"

int main()
{
	std::vector<Point> point;
	IFile* test = FileFactory::Open("test.csv", "r");
	test->Read(point);
	std::cout << point.size();

}