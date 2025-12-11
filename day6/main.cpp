#include "../fileOpener.cpp"

std::vector<std::vector<long long>> ParseInputNums(std::vector<std::string> inputLines);
std::vector<long long> ParseNumLine(std::string inputLine);
std::vector<char> GetOperations(std::string lineOps);
std::vector<long long> DoMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations);
//doing this is actually gonna make us do maff horizontally again lmao
std::vector<long long> DoSidewaysMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations);
std::vector<std::vector<long long>> GetNumsTheLongWay(std::vector<std::vector<long long>> maffNums);
std::vector<long long> ParseNumsTheLongWay(std::vector<long long> maffNumsToParse);
long long GetGrandTotal(std::vector<long long> maffAnswers);

int main()
{
	std::vector<std::string> fileInput = openFile("sample");

	//mathematical
	std::vector<std::vector<long long>> numsForProbs = ParseInputNums(fileInput);
	std::vector<char> operations = GetOperations(fileInput[fileInput.size() - 1]);
	std::vector<long long> individualAnswers = DoMaff(numsForProbs, operations);
	long long grandTotal = GetGrandTotal(individualAnswers);

	for(int i = 0; i < individualAnswers.size(); i++)
		std::cout << "Answer " << i << ": "  << individualAnswers[i] << std::endl;

	std::cout << "Grand total answer: " << grandTotal << std::endl;

	return 0;
}

std::vector<std::vector<long long>> ParseInputNums(std::vector<std::string> inputLines)
{
	std::vector<std::vector<long long>> returnInputs;

	//we aint doin ops here yo
	for(int i = 0; i < inputLines.size() - 1; i++)
		//parse each line
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

std::vector<long long> DoSidewaysMaff(std::vector<std::vector<long long>> maffNums, std::vector<char> operations)
{

}

std::vector<std::vector<long long>> GetNumsTheLongWay(std::vector<std::vector<long long>> maffNums)
{
	std::vector<std::vector<long long>> horizontalMaffNums;

	for(int i = 0; i < maffNums.size(); i++)
	{
		std::vector<long long> tempNums;
		for(int j = 0; j < maffNums[i].size(); j++)
		{
			
		}
	}

	return horizontalMaffNums;
}

std::vector<long long> ParseNumsTheLongWay(std::vector<long long> maffNumsToParse);
{

}

long long GetGrandTotal(std::vector<long long> maffAnswers)
{
	long long grandTotal = 0;
	for(int i = 0; i < maffAnswers.size(); i++)
		grandTotal += maffAnswers[i];

	return grandTotal;
}