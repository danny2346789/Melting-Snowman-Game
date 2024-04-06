#include "randomword.hpp"

int GenerateRandomNumber(int min, int max)
{
	random_device rd{};
	seed_seq ss{ rd(), rd(), rd(), rd() };
	mt19937 merTwister{ ss };
	uniform_int_distribution<> numberRange{ min,max };

	int randomNumber = numberRange(merTwister);
	return randomNumber;
}

string FindLineInFile(int lineNumber, const char* filepath)
{
	std::ifstream file(filepath);
	string line;
	string word;

	int currentLine = 0;

	if (file.is_open())
	{
		while (std::getline(file, line)) {

			if (currentLine == lineNumber) {
				word = line;
				break;
			}
			++currentLine;
		}
		file.close();
		return word;
	}
	else
		throw std::ifstream::failure("FindLineInFile: Could not load the wordlist!\n");
	
	file.close();
	return "";
}