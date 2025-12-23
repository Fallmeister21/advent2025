#include "../fileOpener.cpp"

int main()
{
	std::vector<std::string> fileInput = openFile("sample");

	for(int i = 0; i < fileInput.size(); i++)
		std::cout << fileInput[i] << std::endl;

	return 0;
}