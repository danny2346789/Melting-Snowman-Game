#pragma once
#include <random>
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::mt19937; 
using std::uniform_int_distribution; 
using std::random_device; 
using std::seed_seq;

int GenerateRandomNumber(int min, int max);
string FindLineInFile(int lineNumber, const char* filepath);