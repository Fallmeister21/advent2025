#include "../fileOpener.cpp"
#include <cmath>

int leffOrRye(char dir);
int parseLine(std::string line);
void overUnderflow(int & currPos, int amt, int & passwd);
void uncPass(int & passwd);
int zeroPasses(int endingPos);

int main()
{
	std::vector<std::string> fileInput = openFile("sample");
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
	currPos += amt;
	currPos %= 100;
	//check how many times 0 will be passed over
	if(currPos < 0 || currPos > 99)
		passwd += zeroPasses(currPos);
	else if(currPos == 0)
		uncPass(passwd);
	//std::cout << "Current Pos: " << currPos <<  " and moved a distance of: " << amt << std::endl;
}

void uncPass(int & passwd)
{
	passwd++;
}

int zeroPasses(int endingPos)
{
	int numPasses = 0;
	
	std::cout << "Total covered distance from " << endingPos << std::endl;
	if(endingPos < 0)
		while(endingPos < 0)
		{
			endingPos += 100;
			numPasses++;
		}
	else if(endingPos > 100)
		while(endingPos > 100)
		{
			endingPos -= 100;
			numPasses++;
		}

	return numPasses;
}