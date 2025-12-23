#include "../fileOpener.cpp"
#include <set>

std::pair<int, int> GetManifoldPos(std::vector<std::string> fileInput);
int GetSplitterPositions(std::vector<std::string> fileInput);

int main()
{
	std::vector<std::string> fileInput = openFile("day7Input");
	std::pair<int, int> manifoldPos =  GetManifoldPos(fileInput);
	int splitterPositions = GetSplitterPositions(fileInput);

	std::cout << "Manifold position: " << manifoldPos.first << "," << manifoldPos.second << std::endl;

	std::cout << "Splitter size: " << splitterPositions << std::endl;

	return 0;
}

std::pair<int, int> GetManifoldPos(std::vector<std::string> fileInput)
{
	std::pair<int, int> returnManifoldPos = { 0, 0 };
	bool foundManifold = false;

	for(int i = 0; i < fileInput.size(); i++)
	{
		for(int j = 0; j < fileInput[i].size(); j++)
			if(fileInput[i][j] == 'S')
			{
				returnManifoldPos.first = i;
				returnManifoldPos.second = j;
				foundManifold = true;
				break;
			}
		if(foundManifold)
			break;
	}

	return returnManifoldPos;
}

int GetSplitterPositions(std::vector<std::string> fileInput)
{
	std::set<int> returnSplitterPositions;
	int beamSplits = 0;

	std::cout << "before looping" << std::endl;

	for(const auto &line : fileInput)
	{
		for(int i = 0; i < line.size(); i++)
		{
			if(line[i] == 'S')
				returnSplitterPositions.insert(i);
			else if(line[i] == '^' && returnSplitterPositions.count(i))
			{
				beamSplits++;
				returnSplitterPositions.erase(i);
				returnSplitterPositions.insert(i - 1);
				returnSplitterPositions.insert(i + 1);
			}
		}
	}

	std::cout << beamSplits << std::endl;
	return beamSplits;
}