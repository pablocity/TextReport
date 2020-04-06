// TextReportApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Utils.h"

struct WordDictionary
{
	std::string word;
	int wordCount;

	WordDictionary(std::string word, int wordCount)
	{
		this->word = word;
		this->wordCount = wordCount;
	}

	bool operator< (const WordDictionary& item)
	{
		return word < item.word;
	}
};


int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "Polish");

	std::string inputPath, outputPath, sortingOrder, error, currentLine;

	std::vector<WordDictionary> words;

	std::ifstream inputFile;

	if (!ParseArguments(argc, argv, inputPath, outputPath, sortingOrder, error))
	{
		std::cout << error << std::endl;
		return -1;
	}

	inputFile.open(inputPath);

	if (inputFile)
	{
		std::string word;
		std::stringstream stream;

		while (getline(inputFile, currentLine))
		{
			stream << currentLine;

			while (stream >> word)
			{
				if (!IncrementIfExists(words, word))
					words.push_back(WordDictionary(word, 1));
			}

			stream = std::stringstream();
		}

		inputFile.close();
	}
	else
	{
		std::cout << "Pojawi³ siê problem z plikiem, spróbuj ponownie.";
		return -1;
	}

	PrintResults(words, outputPath, sortingOrder);
}

bool ParseArguments(int count, char* args[], std::string& input, std::string& output, std::string& order, std::string& error)
{
	if (count != 4)
	{
		error = "Liczba argumentów jest nieprawid³owa, podaj kolejno: œcie¿ê wejœciow¹, œcie¿kê wyjœciow¹ oraz kolejnoœæ sortowania 'asc' lub 'desc'";
		return false;
	}

	if (!FileExists(std::string(args[1])))
	{
		error = "Œcie¿ka pliku wejœciowego jest nieprawid³owa, plik musi istnieæ na dysku.";
		return false;
	}

	std::cout << args[3];

	std::string orderString(args[3]);

	if (orderString != "asc" && orderString != "desc")
	{
		std::cout << args[3];
		error = "Podaj kolejnoœæ sortowania w odpowiednim formacie: 'asc' - rosn¹co lub 'desc' - malej¹co.";
		return false;
	}

	input = args[1];
	output = args[2];
	order = args[3];

	return true;
}

bool FileExists(std::string path)
{
	std::fstream file;
	file.open(path);
	bool exists = false;

	if (!file)
		exists = false;
	else
		exists = true;

	std::cout << path;

	file.close();

	return exists;
}

bool IncrementIfExists(std::vector<WordDictionary>& list, std::string element)
{
	for (WordDictionary& item : list)
	{
		if (item.word == element)
		{
			++(item.wordCount);
			return true;
		}
	}

	return false;
}

void PrintResults(std::vector<WordDictionary> list, std::string outputPath, std::string order)
{

	std::ofstream output(outputPath);

	if (!output)
	{
		std::cout << "Nieprawid³owa œcie¿ka pliku wyjœciowego.";
		return;
	}
		

	SortElements(list, order);

	std::cout << "List s³ów w pliku oraz liczba ich wystêpowania: " << std::endl;

	std::string line;

	for (WordDictionary item : list)
	{
		line = item.word + " liczba wyst¹pieñ: " + std::to_string(item.wordCount);
		std::cout << line << std::endl;
		output << line << "\n";
	}

	output.close();
}

void SortElements(std::vector<WordDictionary>& list, std::string order)
{
	if (order == "desc")
		std::sort(list.rbegin(), list.rend());
	else
		std::sort(list.begin(), list.end());
}
