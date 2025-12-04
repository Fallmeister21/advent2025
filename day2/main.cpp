#include "../fileOpener.cpp"
#include <regex>
#include "cmath"

long long loopRange(long long beginning, long long end);
long long parseString(long long inNum);

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
			std::cout << "Current Total invalid id count: " << totalInvalidIds << std::endl;

			realLine = foundDigiPairs.suffix().str();
		}
	}
	std::cout << "Total invalid id count: " << totalInvalidIds << std::endl;
	return 0;
}

long long loopRange(long long beginning, long long end)
{
	long long foundInvalids = 0;
	while(beginning < end + 1)
	{
		if(parseString(beginning) != 0)
			foundInvalids += parseString(beginning);
		beginning++;
	}

	std::cout << std::endl;
	return foundInvalids;
}

long long parseString(long long inNum)
{
	std::string intString = std::to_string(inNum), fHalfString, lHalfString;
	int startPos = 0;

	if(intString.size() % 2 != 0)
		return 0;

	startPos = (intString.size() / 2);

	fHalfString = intString.substr(0, startPos);
	lHalfString = intString.substr(startPos);
	if(fHalfString == lHalfString)
		return inNum;

	return 0;
}