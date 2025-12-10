#include "../fileOpener.cpp"
#include <utility>

std::vector<int> GetLinesToCheck(int currentLine, int maxLineSize);
std::vector<std::pair<int, std::string>> createGoodPassableVector(std::vector<std::string> & currLines, std::vector<int> & lookingLines, int currentLine);
bool checkRollOfPaper(std::vector<std::pair<int, std::string>> mulRowsToCheck, std::pair<int,int> posLine);
int checkForAboveBelow(std::vector<std::pair<int, std::string>> mulRowsToCheck, std::pair<int, int> linePos);
int checkForNextToSpace(std::string sinRowToCheck, int pos, bool isCurrentLine);

int main()
{
	std::vector<std::string> fileInput = openFile("day4Input");
	int movableRolls = 0;

	for(int i = 0; i < fileInput.size(); i++)
	{
		std::vector<int> lines2Check = GetLinesToCheck(i, fileInput[i].size()); //just 3 we be lookin at yo

		//from previous to next (ranged)
		std::vector<std::pair<int, std::string>> linesPassed = createGoodPassableVector(fileInput, lines2Check, i);

		for(int j = 0; j < fileInput[i].size(); j++)
		{
			if(fileInput[i][j] == '@')
			{
				//pair of line position
				auto linePosPair = std::make_pair(i,j);
				if(checkRollOfPaper(linesPassed, linePosPair))
				{
					fileInput[i][j] = 'x';
					movableRolls++;
				}
			}
		}
	}

	//re-output to check how we did
	for(int i = 0; i < fileInput.size(); i++)
	{
		for(int j = 0; j < fileInput[i].size(); j++)
			std::cout << fileInput[i][j];
		std::cout << std::endl;
	}
	std::cout << "Movable rolls: " << movableRolls << std::endl;
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
		returnLinesWithNums.push_back({tempPair});
		if(lineWeAreCurrentlyLookingAtFromVector == currentLine)
			insertedCurrentLine = true;
	}

	return returnLinesWithNums;
}

bool checkRollOfPaper(std::vector<std::pair<int, std::string>> mulRowsToCheck, std::pair<int,int> posLine)
{
	int rollCount = 0;
	bool canMoveRollaPaper = false;
	rollCount = checkForAboveBelow(mulRowsToCheck, posLine);

	if(rollCount < 4)
		return true;
	
	return canMoveRollaPaper;
}

int checkForAboveBelow(std::vector<std::pair<int, std::string>> mulRowsToCheck, std::pair<int, int> linePos)
{
	int returnCount = 0;

	for(int i = 0; i < mulRowsToCheck.size(); i++)
	{
		std::string currentLineString = mulRowsToCheck[i].second;
		//check the current line
		returnCount += checkForNextToSpace(currentLineString, linePos.second, 
		true ? mulRowsToCheck[i].first == linePos.first : false);
	}
	return returnCount;
}

int checkForNextToSpace(std::string sinRowToCheck, int pos, bool isCurrentLine)
{
	//simpler than syrup
	int returnCount = 0;

	if(!isCurrentLine && 
	  (sinRowToCheck[pos]     == '@' || sinRowToCheck[pos]     == 'x'))
		returnCount++;
	if(sinRowToCheck[pos + 1] == '@' || sinRowToCheck[pos + 1] == 'x')
		returnCount++;
	if(sinRowToCheck[pos - 1] == '@' || sinRowToCheck[pos - 1] == 'x')
		returnCount++;
	return returnCount;
}