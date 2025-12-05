#include "../fileOpener.cpp"
#include <regex>
#include "cmath"

long long loopRange(long long beginning, long long end);
long long parseString(long long inNum, bool & part1Checker);
bool parseRepeatPattern(long long inNum);

int main()
{
	std::vector<std::string> fileInput = openFile("day2Input");
	//because of the implication
	std::string realLine = fileInput[0];
	//then they cant refuse
	std::string foundDigits;

	//regex stuff
	std::smatch foundDigiPairs;
	std::regex stateMatch("\\d+-\\d+");
	long long totalInvalidIds = 0;

	while(std::regex_search(realLine, foundDigiPairs, stateMatch))
	{
		std::string workingFind = foundDigiPairs.str(0);

		//guaranteed to be here
		std::string::size_type pos1 = workingFind.find('-');

		if(pos1 != std::string::npos)
		{
			long long num1 = std::stoll(workingFind.substr(0, pos1));
			long long num2 = std::stoll(workingFind.substr(pos1 + 1));

			std::cout << "Range: " << num1 << " - " << num2 << std::endl;
			totalInvalidIds += loopRange(num1, num2);

			realLine = foundDigiPairs.suffix().str();
		}
	}
	std::cout << "Total invalid id count: " << totalInvalidIds << std::endl;
	return 0;
}

long long loopRange(long long beginning, long long end)
{
	long long foundInvalids = 0;
	bool alreadyExisted = false;
	for(long long start = beginning; start <= end; start++)
	{
		//std::cout << "Checking " << start << std::endl;
		if(parseString(start, alreadyExisted) != 0)
		{
			alreadyExisted = false;
			foundInvalids += parseString(start, alreadyExisted);
			if(!alreadyExisted)
				std::cout << "Invalid id part 2 at " << start << std::endl;
			else
				std::cout << "Invalid id part 1 at " << start << std::endl;
		}
	}

	std::cout << std::endl;
	return foundInvalids;
}

long long parseString(long long inNum, bool & part1Checker)
{
	
	std::string intString = std::to_string(inNum), fHalfString, lHalfString;
	int startPos = 0;
	startPos = (intString.size() / 2);

	fHalfString = intString.substr(0, startPos);
	lHalfString = intString.substr(startPos);

	if(fHalfString == lHalfString)
	{
		part1Checker = true;
		return inNum;
	}
	if(parseRepeatPattern(inNum))
		return inNum;

	return 0;
}

bool parseRepeatPattern(long long inNum)
{
	std::string numString = std::to_string(inNum);
	int numLength = numString.size();
	bool isValid = false, validResult = false;

	if(numLength > 1)
	{
		for(int patternLen = 1; patternLen <= numLength / 2; patternLen++)
		{
			std::string currPattern = numString.substr(0, patternLen);
			int posCount = 0;
			isValid = false;

			for (int i = 1; i <= numLength; i += patternLen)
			{
				if(currPattern == numString.substr(i - 1, patternLen))
				{
					posCount += patternLen;
					continue;
				}
				else
				{
					isValid = true;
					break;
				}
			}
			if(!isValid && posCount == numLength)
			{
				validResult = true;
				break;
			}
		}
	}
	return validResult;
}
