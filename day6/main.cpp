#include "../fileOpener.cpp"

std::vector<std::vector<long long>> ParseInputNums(std::vector<std::string> inputLines);
std::vector<long long> ParseNumLine(std::string inputLine);
std::vector<std::string> ParseStringLine(std::vector<std::string> inputLines);
std::vector<char> GetOperations(std::string lineOps);
std::vector<long long> DoMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations);
//doing this is actually gonna make us do maff horizontally again lmao
std::vector<std::vector<long long>> TransposeConstructedNumString(std::vector<std::string> inLongStrings, int groupSize, std::vector<char> operations);
std::vector<long long> DoSidewaysMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations);
long long GetGrandTotal(std::vector<long long> maffAnswers);

int main()
{
	std::vector<std::string> fileInput = openFile("day6Input");

	//mathematical
	std::vector<std::vector<long long>> numsForProbs = ParseInputNums(fileInput);
	std::vector<std::string> numsForSidewaysProbs = ParseStringLine(fileInput);
	std::vector<char> operations = GetOperations(fileInput[fileInput.size() - 1]);
	std::vector<long long> individualAnswers = DoMaff(numsForProbs, operations);
	long long grandTotal = GetGrandTotal(individualAnswers);

	std::vector<std::vector<std::string>> stringNumsForSidewaysProbs = {};
	for(int i = 0; i < numsForSidewaysProbs.size(); i++)
	{
		stringNumsForSidewaysProbs.push_back({});
		for(int j = 0; j < numsForSidewaysProbs[i].size(); j++)
			stringNumsForSidewaysProbs[i].push_back(std::to_string(numsForSidewaysProbs[i][j]));
	}

	std::vector<std::vector<long long>> sidewaysNumbers = TransposeConstructedNumString(numsForSidewaysProbs, operations.size(), operations);

	std::vector<long long> sidewaysAnswers = DoSidewaysMaff(sidewaysNumbers, operations);
	long long sidewaysGrandTotal = GetGrandTotal(sidewaysAnswers);

	for(int i = 0; i < individualAnswers.size(); i++)
		std::cout << "Answer " << i << ": "  << individualAnswers[i] << std::endl;

	std::cout << std::endl;

	for(int i = 0; i < sidewaysAnswers.size(); i++)
		std::cout << "Sideways answer " << i << ": "  << sidewaysAnswers[i] << std::endl;

	std::cout << "Grand total answer: " << grandTotal << std::endl;
	std::cout << "Sideways grand total answer: " << sidewaysGrandTotal << std::endl;

	return 0;
}

std::vector<std::vector<long long>> ParseInputNums(std::vector<std::string> inputLines)
{
	std::vector<std::vector<long long>> returnInputs;

	//we aint doin ops here yo
	for(int i = 0; i < inputLines.size() - 1; i++)
		returnInputs.push_back(ParseNumLine(inputLines[i]));

	return returnInputs;
}

std::vector<long long> ParseNumLine(std::string inputLine)
{
	std::vector<long long> returnNums;
	std::string tempNum = ""; // yeah right

	for(int i = 0; i <= inputLine.size(); i++)
	{
		if(!std::isspace(inputLine[i]) && inputLine[i] != '\0')
			tempNum += inputLine[i];
		else if(tempNum != "")
		{
			returnNums.push_back(std::stoll(tempNum));
			tempNum = "";
		}
	}

	return returnNums;
}

std::vector<std::string> ParseStringLine(std::vector<std::string> inputLines)
{
	std::vector<std::string> returnInputs;
	std::vector<std::string> returnNums;

	//we aint doin ops here yo
	for(int i = 0; i < inputLines.size() - 1; i++)
	{
		std::string tempNum = ""; // yeah right
		for(int j = 0; j <= inputLines[i].size(); j++)
		{
			if(inputLines[i][j] != '\0')
				tempNum += inputLines[i][j];
			else if(tempNum != "")
			{
				break;
			}
		}
		returnInputs.push_back(tempNum);
		tempNum = "";
	}

	return returnInputs;
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

std::vector<std::vector<long long>> TransposeConstructedNumString(std::vector<std::string> inLongStrings, int groupSize, std::vector<char> operations)
{
	std::vector<std::vector<std::string>> returnStringLong;
	std::vector<std::vector<long long>> returnLong;
	std::vector<long long> tempLongs;

	for(int i = inLongStrings[0].size() - 1; i >= 0; i--)
	{
		std::string tempNum = "";
		//for each character in the string
		for(int j = 0; j < inLongStrings.size(); j++)
			if(!std::isspace(inLongStrings[j][i]))
				tempNum += inLongStrings[j][i];
		if(tempNum.size() > 0 && std::stoll(tempNum) != 0)
			tempLongs.push_back(std::stoll(tempNum));
		else
		{
			returnLong.push_back(tempLongs);
			tempLongs = {};
		}
	}
	returnLong.push_back(tempLongs);

	return returnLong;
}

std::vector<long long> DoSidewaysMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations)
{
	std::vector<long long> maffAnswers;
	long long answer = 0;

	std::reverse(operations.begin(), operations.end());

	for(int i = 0; i < maffNums.size(); i++)
	{
		for(int j = 0; j < maffNums[i].size(); j++)
		{
			std::cout << "math number: " << maffNums[i][j] << std::endl;
			if(operations[i] == '+')
				answer += maffNums[i][j];
			else if(operations[i] == '*')
			{
				if(answer == 0)
					answer = maffNums[i][j];
				else
					answer = answer * maffNums[i][j];
			}
		}
		std::cout << std::endl;
		if(answer != 0)
		{
			maffAnswers.push_back(answer);
			answer = 0;
		}
	}
	

	return maffAnswers;
}

long long GetGrandTotal(std::vector<long long> maffAnswers)
{
	long long grandTotal = 0;
	for(int i = 0; i < maffAnswers.size(); i++)
		grandTotal += maffAnswers[i];

	return grandTotal;
}