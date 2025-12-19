#include "../fileOpener.cpp"

std::vector<std::vector<long long>> ParseInputNums(std::vector<std::string> inputLines, bool part2);
std::vector<long long> ParseNumLine(std::string inputLine, bool part2);
std::vector<char> GetOperations(std::string lineOps);
std::vector<long long> DoMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations);
//doing this is actually gonna make us do maff horizontally again lmao
std::vector<std::vector<long long>> TransposeConstructedNumString(std::vector<std::vector<std::string>> inLongStrings, int groupSize, std::vector<char> operations);
std::vector<long long> ParseSpacedSidewaysNums(std::vector<std::string> toParseSet, int longestString);
std::string GetLongestValue(std::vector<std::vector<std::string>> maffNums, int groupToView);
std::vector<long long> DoSidewaysMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations);
long long GetGrandTotal(std::vector<long long> maffAnswers);

int main()
{
	std::vector<std::string> fileInput = openFile("sample");

	//mathematical
	std::vector<std::vector<long long>> numsForProbs = ParseInputNums(fileInput, false);
	std::vector<std::vector<std::string>> numsForSidewaysProbs = ParseInputStrings(fileInput, true);
	std::vector<char> operations = GetOperations(fileInput[fileInput.size() - 1]);
	// std::vector<long long> individualAnswers = DoMaff(numsForProbs, operations);
	// long long grandTotal = GetGrandTotal(individualAnswers);

	std::vector<std::vector<long long>> sidewaysNumbers = TransposeConstructedNumString(numsForSidewaysProbs, operations.size(), operations);
	for(int i = 0; i < numsForSidewaysProbs.size(); i++)
	{
		for(int j = 0; j < numsForSidewaysProbs[i].size(); j++)
			std::cout << "Sideways number " << i << " " << j << ": " << numsForSidewaysProbs[i][j] << std::endl;
		std::cout << std::endl;
	}

	//std::vector<long long> sidewaysAnswers = DoSidewaysMaff(sidewaysNumbers, operations);
	//long long sidewaysGrandTotal = GetGrandTotal(sidewaysAnswers);

	//for(int i = 0; i < individualAnswers.size(); i++)
	//	std::cout << "Answer " << i << ": "  << individualAnswers[i] << std::endl;

	std::cout << std::endl;

	// for(int i = 0; i < sidewaysAnswers.size(); i++)
	// 	std::cout << "Sideways answer " << i << ": "  << sidewaysAnswers[i] << std::endl;

	// //std::cout << "Grand total answer: " << grandTotal << std::endl;
	// std::cout << "Sideways grand total answer: " << sidewaysGrandTotal << std::endl;

	return 0;
}

std::vector<std::vector<long long>> ParseInputNums(std::vector<std::string> inputLines, bool part2)
{
	std::vector<std::vector<long long>> returnInputs;

	//we aint doin ops here yo
	for(int i = 0; i < inputLines.size() - 1; i++)
		returnInputs.push_back(ParseNumLine(inputLines[i], part2));

	return returnInputs;
}

std::vector<long long> ParseNumLine(std::string inputLine, bool part2)
{
	std::vector<long long> returnNums;
	std::string tempNum = ""; // yeah right

	for(int i = 0; i <= inputLine.size(); i++)
	{
		if(!part2 && !std::isspace(inputLine[i]) && inputLine[i] != '\0')
			tempNum += inputLine[i];
		else if(part2 && inputLine[i] != '\0')
		else if(tempNum != "")
		{
			returnNums.push_back(std::stoi(tempNum));
			tempNum = "";
		}
	}

	return returnNums;
}

std::vector<char> GetOperations(std::string lineOps)
{
	//NOT a string :)
	std::vector<char> returnOps;

	for(int i = 0; i < lineOps.size(); i++)
		if(!std::isspace(lineOps[i]) && lineOps[i] != '\0')
			returnOps.push_back(lineOps[i]);

	return returnOps;
}

std::vector<long long> DoMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations)
{
	std::vector<long long> maffAnswers;

	//one operation for each set of numbers
	for(int i = 0; i < operations.size(); i++)
	{
		long long answer = 0;
		//for each set of maff nums
		for(int j = 0; j < maffNums.size(); j++)
		{
			if(operations[i] == '+')
				answer += maffNums[j][i];
			else if(operations[i] == '*')
			{
				if(answer == 0)
					answer = maffNums[j][i];
				else
					answer *= maffNums[j][i];
			}
		}
		maffAnswers.push_back(answer);
	}

	return maffAnswers;
}

std::vector<std::vector<long long>> TransposeConstructedNumString(std::vector<std::vector<std::string>> inLongStrings, int groupSize, std::vector<char> operations)
{
	std::vector<std::vector<std::string>> returnStringLong;
	std::vector<std::vector<long long>> returnLong;

	int maxLongString = GetLongestValue(inLongStrings, 0).length();
	for(int i = 0; i < groupSize; i++)
	{
		std::vector<std::string> tempLongs;
		//for each set of maff nums
		//make a function here to get max value of the 'set' i want
		
		//std::cout << " max length here: \"" << maxLongString << "\"" <<  std::endl;
		for(int j = 0; j < inLongStrings[i].size(); j++)
		{
			std::string tempNum = "";
			//for each 'column' in numbers given
			for(int k = 0; k < maxLongString; k++)
			{	
				if(inLongStrings[i][j][k] != '\0')
					//screw it, everything is a vector
					tempNum += inLongStrings[i][j][k];
			}
			std::cout << " looking at temp num here: \"" << tempNum << "\"" <<  std::endl;
			tempLongs.push_back(tempNum);
		}
		std::cout << std::endl;
		returnStringLong.push_back(tempLongs);
	}

	//ok, got where they should be now just do the line maff
	// for(int i = 0; i < returnStringLong.size(); i++)
	// 	returnLong.push_back(ParseSpacedSidewaysNums(returnStringLong[i], maxLongString));

	// for(int i = 0; i < returnLong.size(); i++)
	// {
	// 	for(int j = 0; j < returnLong[i].size(); j++)
	// 		std::cout << "looking at sideways maff num: \"" << returnLong[i][j] << "\"" <<  std::endl;
	// 	std::cout << std::endl;
	// }

	return returnLong;
}

std::vector<long long> ParseSpacedSidewaysNums(std::vector<std::string> toParseSet, int longestString)
{
	std::vector<long long> parsedStringLong;

	//int maxLongString = GetLongestValue({toParseSet}, 0).length();
	int maxLongString = longestString;
	for(int i = 0; i < maxLongString; i++)
	{
		std::string tempLong = "";
		//std::cout << "looping through: " << toParseSet[i] << std::endl;
		std::cout << "max long string: " << maxLongString << std::endl;
		for(int j = 0; j < toParseSet.size(); j++)
		{
			std::cout << "current number: " << toParseSet[j] << std::endl;
			if(!std::isspace(toParseSet[j].back()) && toParseSet[j].back() != '\0')
			{
				tempLong += toParseSet[j].back();
				toParseSet[j] = toParseSet[j].substr(0, toParseSet[j].length() - 1);
			}
			std::cout << "value here: \"" << tempLong << "\"" << "at i: " << i << " and j: " << j << std::endl;
			//if(!std::isspace(toParseSet[j][i]) && toParseSet[j][i] != '\0')
			//	tempLong += toParseSet[j][i];
		}
		if(tempLong != "")
		{
			//std::reverse(tempLong.begin(), tempLong.end());
			parsedStringLong.push_back(std::stoll(tempLong));
		}
		std::cout << std::endl;
	}
	//std::cout << std::endl;

	return parsedStringLong;
}

std::vector<long long> DoSidewaysMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations)
{
	std::vector<long long> maffAnswers;

	//one operation for each set of numbers
	for(int i = 0; i < operations.size(); i++)
	{
		long long answer = 0;
		//for each set of maff nums
		for(int j = 0; j < maffNums.size() - 1; j++)
		{
			std::cout << "math number: " << maffNums[i][j] << std::endl;
			if(operations[i] == '+')
				answer += maffNums[i][j];
			else if(operations[i] == '*')
			{
				if(answer == 0)
					answer = maffNums[i][j];
				else
					answer *= maffNums[i][j];
			}
		}
		std::cout << std::endl;
		maffAnswers.push_back(answer);
	}

	return maffAnswers;
}

std::string GetLongestValue(std::vector<std::vector<std::string>> maffNums, int groupToView)
{
	std::string longestValue = "";
	for(int i = 0; i < maffNums[groupToView].size(); i++)
		if(maffNums[groupToView][i].length() > longestValue.length())
			longestValue = maffNums[groupToView][i];
	
	return longestValue;
}


long long GetGrandTotal(std::vector<long long> maffAnswers)
{
	long long grandTotal = 0;
	for(int i = 0; i < maffAnswers.size(); i++)
		grandTotal += maffAnswers[i];

	return grandTotal;
}