#include "../fileOpener.cpp"
#include <utility>

std::vector<int> GetLinesToCheck(int currentLine, int maxLineSize);
std::vector<std::pair<int, std::string>> createGoodPassableVector(std::vector<std::string> & currLines, std::vector<int> & lookingLines, int currentLine);
bool checkRollOfPaper(std::vector<std::pair<int, std::string>> mulRowsToCheck, int currentPos);
bool checkForAboveBelow(int direction);
bool checkForNextToSpace(std::vector<std::string> sinRowToCheck);

int main()
{
	std::vector<std::string> fileInput = openFile("sample");
	;

	for(int i = 0; i < fileInput.size(); i++)
	{
		//std::cout << "Line number " << i << ": " << fileInput[i] << std::endl;
		std::vector<int> lines2Check = GetLinesToCheck(i, fileInput[i].size()); //just 3 we be lookin at yo

		//from previous to next (ranged)
		std::vector<std::pair<int, std::string>> linesPassed = createGoodPassableVector(fileInput, lines2Check, i);
		for(int k = 0; k < linesPassed.size(); k++)
			std::cout << "Checking this weird setup: Line-> " << linesPassed[k].first << " line value-> " << linesPassed[k].second << std::endl;
		std::cout << std::endl;

		//for(int j = 0; j < fileInput[i].size(); j++)
		{
			bool goodRollOfPaper = false;

			//if(fileInput[i][j] == '@')
			{
				//goodRollOfPaper = checkRollOfPaper(linesPassed, j);
				
			}
			//std::cout << "PrevLine: " << lines2Check[0] << " CurrentLine: " << lines2Check[1] << " NextLine: " << lines2Check[2] << std::endl;
		}
	}
	return 0;
}

std::vector<int> GetLinesToCheck(int currentLine, int maxLineSize)
{
	std::vector<int> returnLines;

	returnLines.push_back(currentLine <= 0 ? 0 : currentLine - 1);                             //previous line
	returnLines.push_back(currentLine);                                                        //current line
	returnLines.push_back(currentLine >= maxLineSize - 1 ? maxLineSize - 1 : currentLine + 1); //next line

	return returnLines;
}

std::vector<std::pair<int, std::string>> createGoodPassableVector(std::vector<std::string> & currLines, std::vector<int> & lookingLines, int currentLine)
{
	std::vector<std::pair<int,std::string>> returnLinesWithNums = {};
	bool insertedCurrentLine = false;

	for(int i = 0; i < lookingLines.size(); i++)
	{
		int lineWeAreCurrentlyLookingAtFromVector = 0;
		lineWeAreCurrentlyLookingAtFromVector = lookingLines[i]; // for brevity
		if(insertedCurrentLine && lineWeAreCurrentlyLookingAtFromVector == currentLine)
			continue;
		auto tempPair = std::make_pair(lineWeAreCurrentlyLookingAtFromVector, currLines[lineWeAreCurrentlyLookingAtFromVector]);
		std::cout << "pushing pair first: " << tempPair.first << " second: " << tempPair.second << std::endl;
		returnLinesWithNums.push_back({tempPair});
		if(lineWeAreCurrentlyLookingAtFromVector == currentLine)
			insertedCurrentLine = true;
	}
	std::cout  << std::endl;

	return returnLinesWithNums;
}

bool checkRollOfPaper(std::vector<std::string> mulRowsToCheck, int currentPos)
{

	return false;
}

bool checkForAboveBelow(int direction)
{
	return false;
}

bool checkForNextToSpace(std::vector<std::string> sinRowToCheck)
{
	return false;
}