#include "../fileOpener.cpp"
#include <utility>

std::vector<int> parseFileLines(std::string inLine);
int getMAXJoltage(std::vector<int> joltageValues);

int main()
{
	std::vector<std::string> fileInput = openFile("sample");
	//BAH - TUH - RAEY
	std::vector<std::vector<int>> batteryLines;
	std::vector<int> individualJotages;
	int totalJoltage = 0;

	for(int i = 0; i < fileInput.size(); i++)
	{
		std::string fileLine = fileInput[i];
		batteryLines.push_back(parseFileLines(fileLine));
	}

	for(int i = 0; i < batteryLines.size(); i++)
	{
		std::vector<int> tempVector = batteryLines[i]; //fine, be that way
		totalJoltage += getMAXJoltage(tempVector);
		for(int j = 0; j < batteryLines[i].size(); j++)
			std::cout << "Battery line " << i << " joltage value " << batteryLines[i][j] << std::endl;
		std::cout << std::endl;
	}
	return 0;
}

std::vector<int> parseFileLines(std::string inLine)
{
	std::vector<int> returnInts;

	for(int i = 0; i < inLine.size(); i++)
	{
		//magic
		char currNum = inLine[i];
		int currNumREAL = currNum - '0';
		returnInts.push_back(currNumREAL);
	}

	return returnInts;
}

int getMAXJoltage(std::vector<int> joltageValues)
{
	int currMaxJoltage = 0;
	int currNextMaxJoltage = 0;
	int currentLookingAtJoltageFromListREAL = 0;

	int returnValuesForInputJoltageListPASSEDIN = 0;

	for(int i = 0; i < joltageValues.size(); i++)
	{
		currentLookingAtJoltageFromListREAL = joltageValues[i];
		if(currMaxJoltage < currentLookingAtJoltageFromListREAL)
		{            //Step 1: secure the keys
			currMaxJoltage = currentLookingAtJoltageFromListREAL;
			currNextMaxJoltage = 0;
		}
			//Step 2: ascend from darkness
		else if(currentLookingAtJoltageFromListREAL > currNextMaxJoltage)
			currNextMaxJoltage = currentLookingAtJoltageFromListREAL;
	}

	std::cout << "Max joltage values from this set: " << currMaxJoltage << " least max: " << currNextMaxJoltage << std::endl;

	return returnValuesForInputJoltageListPASSEDIN; //what did you expect
}
