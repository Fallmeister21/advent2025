#include "../fileOpener.cpp"
#include <utility>
#include <algorithm>

std::pair<long long,long long> GetRanges(std::string unparsedRange);
long long GetProductNum(std::string prodLine);
bool ProductIsFresh(std::pair<long long, long long> range, long long prodNum);
void SortProductRanges(std::vector<std::pair<long long, long long>> & prodRanges);
std::vector<int> GetRangeIndexes(std::vector<std::pair<long long, long long>> & prodRanges);

int main()
{
	std::vector<std::string> fileInput = openFile("sample");
	std::vector<std::pair<long long,long long>> freshnessRanges;
	std::vector<long long> prodNums;
	std::vector<int> endRanges;

	bool finishedWithRanges = false;
	int numFreshProds = 0;

	for(int i = 0; i < fileInput.size(); i++)
	{
		if(fileInput[i] == "")
			finishedWithRanges = true;
		else if(!finishedWithRanges)
			freshnessRanges.push_back(GetRanges(fileInput[i]));
		else if(finishedWithRanges)
			prodNums.push_back(GetProductNum(fileInput[i]));
	}

	for(int i = 0; i < prodNums.size(); i++)
	{
		bool prodIsFresh = false;
		for(int j = 0; j < freshnessRanges.size(); j++)
		{
			if(!prodIsFresh && ProductIsFresh(freshnessRanges[j], prodNums[i]))
			{
				numFreshProds++;
				prodIsFresh = true;
			}
		}
	}

	for(int i = 0; i < freshnessRanges.size(); i++)
		std::cout << "Before: " << freshnessRanges[i].first << " " << freshnessRanges[i].second << std::endl;
	std::cout << std::endl;

	SortProductRanges(freshnessRanges);

	for(int i = 0; i < freshnessRanges.size(); i++)
		std::cout << "After: " << freshnessRanges[i].first << " " << freshnessRanges[i].second << std::endl;
	std::cout << std::endl;

	std::cout << "Num of fresh products: " << numFreshProds << std::endl;

	return 0;
}

std::pair<long long,long long> GetRanges(std::string unparsedRange)
{
	std::pair<long long, long long> returnRange;

	long long lowRange = 0;
	long long highRange = 0;
	int delimPos = unparsedRange.find('-');

	lowRange = std::stoll(unparsedRange.substr(0, delimPos));
	highRange = std::stoll(unparsedRange.substr(delimPos + 1, unparsedRange.size()));

	returnRange = std::make_pair(lowRange, highRange);

	return returnRange;
}

long long GetProductNum(std::string prodLine)
{
	long long returnProdNum = 0;

	returnProdNum = std::stoll(prodLine);

	return returnProdNum;
}

bool ProductIsFresh(std::pair<long long, long long> range, long long prodNum)
{
	if(prodNum >= range.first && prodNum <= range.second)
		return true;
	return false;
}

void SortProductRanges(std::vector<std::pair<long long, long long>> & prodRanges)
{
	bool swappedStyle = true;
	while(swappedStyle)
	{
		swappedStyle = false;
		for(int i = 0; i < prodRanges.size() - 1; i++)
		{
			std::pair<int, int> tempPair;
			if(prodRanges[i].first > prodRanges[i + 1].first)
			{
				tempPair = prodRanges[i];
				prodRanges[i] = prodRanges[i + 1];
				prodRanges[i + 1] = tempPair;
				swappedStyle = true;
			}
		}
	}
	return;
}

std::vector<int> GetRangeIndexes(std::vector<std::pair<long long, long long>> & prodRanges)
{
	std::vector<int> returnRangeIndexes;

	for(int i = 0; i < prodRanges.size(); i++)
	{
		
	}

	return returnRangeIndexes;
}