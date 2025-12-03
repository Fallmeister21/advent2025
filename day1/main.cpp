#include "../fileOpener.cpp"

int leffOrRye(char dir);
int parseLine(std::string line);
void overUnderflow(int & currPos, int amt, int & passwd);
void uncPass(int & passwd);

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
	currPos += amt;
	currPos %= 100;
	if(currPos == 0)
	{
		uncPass(passwd);
		std::cout << "Current Passwd: " << passwd << std::endl;
	}
	std::cout << "Current Pos: " << currPos <<  " and moved a distance of: " << amt << std::endl;
}

void uncPass(int & passwd)
{
	passwd++;
}