#include <string.h>

#pragma once

struct WordDictionary;

bool ParseArguments(int count, char* args[], std::string& input, std::string& output, std::string& order, std::string& error);

bool FileExists(std::string path);

bool IncrementIfExists(std::vector<WordDictionary>& list, std::string element);

void SortElements(std::vector<WordDictionary>& list, std::string order);

void PrintResults(std::vector<WordDictionary> list, std::string outputPath, std::string order);
