#include "../fileOpener.cpp"
#include <utility>
#include <algorithm>

//part1
std::vector<int> parseFileLinesPart1(std::string inLine);
int getMAXJoltagePart1(std::vector<int> joltageValues);
void GetMaxJoltagePart1REAL(int & totalJoltagePart1, std::vector<std::vector<int>> batteryLinesPart1);

//part2
long long getMAXJoltagePart2(std::vector<int> joltageValues);
void GetMaxJoltagePart2REAL(long long & totalJoltagePart2, std::vector<std::vector<int>> batteryLinesPart2);
std::vector<int> getLargestValuePositions(std::vector<int> joltageValues);
long long convertMaxesToStringToLongLong(std::vector<int> maxValues);

int main()
{
	std::vector<std::string> fileInput = openFile("day3Input");
	std::vector<std::vector<int>> batteryLinesPart1;
	std::vector<std::vector<int>> batteryLinesPart2;
	//BAH - TUH - RAEY
	int totalJoltagePart1 = 0;
	long long totalJoltagePart2 = 0;

	for(int i = 0; i < fileInput.size(); i++)
	{
		std::string fileLine = fileInput[i];
		batteryLinesPart1.push_back(parseFileLinesPart1(fileLine));
		batteryLinesPart2.push_back(parseFileLinesPart1(fileLine));
	}

	GetMaxJoltagePart1REAL(totalJoltagePart1, batteryLinesPart1);
	GetMaxJoltagePart2REAL(totalJoltagePart2, batteryLinesPart2);

	std::cout << "MAXIMUM joltage phantom blood style: " << totalJoltagePart1 << std::endl;
	std::cout << "MAXIMUM joltage battle tendency style: " << totalJoltagePart2 << std::endl; //heh
	return 0;
}

std::vector<int> parseFileLinesPart1(std::string inLine)
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

int getMAXJoltagePart1(std::vector<int> joltageValues)
{
	int currMaxJoltage = 0;
	int currNextMaxJoltage = 0;
	int currentLookingAtJoltageFromListREAL = 0;

	int returnValuesForInputJoltageListPASSEDIN = 0;

	for(int i = 0; i < joltageValues.size(); i++)
	{
		currentLookingAtJoltageFromListREAL = joltageValues[i];
		if(currMaxJoltage < currentLookingAtJoltageFromListREAL && i + 1 != joltageValues.size())
		{
			currMaxJoltage = currentLookingAtJoltageFromListREAL;
			currNextMaxJoltage = 0;
		}
		else if(currentLookingAtJoltageFromListREAL > currNextMaxJoltage)
			currNextMaxJoltage = currentLookingAtJoltageFromListREAL;
	}
	//std::cout << "Max joltage values from this set: " << currMaxJoltage << " least max: " << currNextMaxJoltage << std::endl;
	std::string returnInit = std::to_string(currMaxJoltage) + std::to_string(currNextMaxJoltage);
	returnValuesForInputJoltageListPASSEDIN = std::stoi(returnInit);

	std::cout << "Constructed total joltage for this set:" << returnValuesForInputJoltageListPASSEDIN << std::endl;

	return returnValuesForInputJoltageListPASSEDIN; //what did you expect
}

void GetMaxJoltagePart1REAL(int & totalJoltagePart1, std::vector<std::vector<int>> batteryLinesPart1)
{
	for(int i = 0; i < batteryLinesPart1.size(); i++)
	{
		std::vector<int> tempVector = batteryLinesPart1[i]; //fine, be that way
		totalJoltagePart1 += getMAXJoltagePart1(tempVector);
		std::cout << std::endl;
	}

	return;
}

long long getMAXJoltagePart2(std::vector<int> joltageValues)
{
	std::vector<int> constructedBatteryList;
	std::vector<int> maxBatteryValuePos;
	long long returnedBatteryValue = 0;

	// remove the 3 smallest values in this bih (positionally)
	constructedBatteryList = getLargestValuePositions(joltageValues);
	//make a giant number string from vector (probably a function here)
	returnedBatteryValue = convertMaxesToStringToLongLong(constructedBatteryList);
	// += as long long to make return value

	return returnedBatteryValue; //what did you expect
}

void GetMaxJoltagePart2REAL(long long & totalJoltagePart2, std::vector<std::vector<int>> batteryLinesPart2)
{
	for(int i = 0; i < batteryLinesPart2.size(); i++)
	{
		std::vector<int> tempVector = batteryLinesPart2[i]; //fine, be that way
		totalJoltagePart2 += getMAXJoltagePart2(tempVector);
		std::cout << std::endl;
	}

	return;
}

std::vector<int> getLargestValuePositions(std::vector<int> joltageValues)
{
	int skippable = joltageValues.size();
	int canSkip = skippable - 12;
	int currentPos = 0;

	std::vector<int> returnJoltages, workingJoltages = joltageValues;
	while(returnJoltages.size() < 12)
	{
		int current = joltageValues[currentPos];

		std::vector<int> joltageWindow = {joltageValues.begin() + currentPos, joltageValues.begin() + currentPos + canSkip + 1};
		if(current >= *(std::max_element(joltageWindow.begin(), joltageWindow.end())))
		{
			currentPos++;
			returnJoltages.push_back(current);
		}
		else
		{
			currentPos++;
			canSkip--;
		}
	}
	return returnJoltages;
}

long long convertMaxesToStringToLongLong(std::vector<int> maxValues)
{
	std::string constructedStringLong;
	long long returnLongLong;
	for(int i = 0; i < maxValues.size(); i++)
		constructedStringLong += std::to_string(maxValues[i]);

	returnLongLong = std::stoll(constructedStringLong);
	std::cout << "Passing back: " << returnLongLong << std::endl;

	return returnLongLong;
}
