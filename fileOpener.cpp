#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fstream>

std::vector<std::string> openFile(std::string fileName)
{
	std::vector<std::string> returnValues;
	std::string lineValue;
	//open input file
	std::ifstream dayFile;
	dayFile.open(fileName);

	if(dayFile.is_open())
	{
		std::getline(dayFile, lineValue);
		returnValues.push_back(lineValue);
	
		while(!dayFile.eof())
		{
			std::getline(dayFile, lineValue);
			if(!dayFile.eof())
				returnValues.push_back(lineValue);
		}
	}
	dayFile.close();

	return returnValues;
}
