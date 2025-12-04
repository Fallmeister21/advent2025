#include "../fileOpener.cpp"
#include <cmath>

int leffOrRye(char dir);
int parseLine(std::string line);
void overUnderflow(int & currPos, int amt, int & passwd);
void uncPass(int & passwd);
int zeroPasses(int startPos, int distance);
int passover(int startPos, int distance, int signage);

int main()
{
	std::vector<std::string> fileInput = openFile("day1Input");
	int password = 0;
	int currentPos = 50;

	std::cout << "Starting pos: " << currentPos << std::endl;
	for(int i = 0; i < fileInput.size(); i++)
	{
		int moveValue = 0;
		std::string line = fileInput[i];
		char dir = line[0];
		//parse dir from amt
		moveValue = parseLine(line);
		//change direction based on direction
		moveValue = leffOrRye(dir) * moveValue;
		//adjust for over/underflow
		overUnderflow(currentPos, moveValue, password);
	}
	std::cout << "Passwd: " << password << std::endl;
	return 0;
}

int leffOrRye(char dir)
{
	if(dir == 'L')
		return -1;
	return 1;
}

int parseLine(std::string line)
{
	return std::stoi(line.substr(1));
}

void overUnderflow(int & currPos, int amt, int & passwd)
{
	int startPos = 0;
	startPos = currPos;
	currPos += amt;
	currPos %= 100;
	//check how many times 0 will be passed over
	passwd += zeroPasses(startPos, amt);
}

void uncPass(int & passwd)
{
	passwd++;
}

int zeroPasses(int startPos, int distance)
{
	int numPasses = 0;

	if(distance < 0)
		numPasses = passover(startPos, distance, -1);
	else
		numPasses = passover(startPos, distance, 1);
	
	if(numPasses != 0 && numPasses != 1)
		std::cout << "Passed 0 this many times: " << numPasses << std::endl;

	return numPasses;
}

int passover(int startPos, int distance, int signage)
{
	int numPasses = 0;

	while(distance != 0)
	{
		startPos += signage;
		if(startPos == 0 || startPos % 100 == 0)
			numPasses++;
		distance += signage * -1;
	}
	return numPasses;
}
