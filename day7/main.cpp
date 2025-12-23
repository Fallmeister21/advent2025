#include "../fileOpener.cpp"
#include <set>
#include <map>

std::pair<int, int> GetManifoldPos(std::vector<std::string> fileInput);
int GetSplitterPositions(std::vector<std::string> fileInput);
long long GetAllTimelines(std::vector<std::string> fileInput);
long long CheckBeamTimelines(std::vector<std::string> fileInput, int i, int j, std::map<std::pair<int, int>, long long> &beamPaths);

int main()
{
	std::vector<std::string> fileInput = openFile("day7Input");
	std::pair<int, int> manifoldPos =  GetManifoldPos(fileInput);
	int splitterPositions = GetSplitterPositions(fileInput);
	long long splitterTimeLines = GetAllTimelines(fileInput);

	std::cout << "Manifold position: " << manifoldPos.first << "," << manifoldPos.second << std::endl;

	std::cout << "Splitter size: " << splitterPositions << std::endl;
	std::cout << "All beam timelines: " << splitterTimeLines << std::endl;

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

long long GetAllTimelines(std::vector<std::string> fileInput)
{
	std::map<std::pair<int, int>, long long> beamPaths;
	long long totalNumberOfTimelines = 0;

	for (int i = 0; i < fileInput[0].length(); i++) {
		char c = fileInput[0][i];
		if (c == 'S') {
			totalNumberOfTimelines = CheckBeamTimelines(fileInput, 0, i, beamPaths);
			break;
		}
	}

	return totalNumberOfTimelines;
}

long long CheckBeamTimelines(std::vector<std::string> fileInput, int i, int j, std::map<std::pair<int, int>, long long> &beamPaths)
{
	if (i == fileInput.size() - 1) {
		return 1;
	}
	if (fileInput[i][j] == '^') {
		if (beamPaths.count({i, j})) {
			return beamPaths.at({i, j});
		}
		long long traces = CheckBeamTimelines(fileInput, i + 1, j - 1, beamPaths) + CheckBeamTimelines(fileInput, i + 1, j + 1, beamPaths);
		beamPaths[{i, j}] = traces;
		return traces;
	}
	return CheckBeamTimelines(fileInput, i + 1, j, beamPaths);
}