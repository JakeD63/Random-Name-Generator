#pragma once

#include <string>
#include <map>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

class Generator
{

//class member functions
public:
	//constructor, takes input names and max length of generated words
	Generator(vector<string> names, int max_length);
	//generates a number of names and returns them as a vector of strings
	vector<string> getNames(int number, bool debug);


//class member variables
private:
	//maps characters to a string of characters that follow in the list of names passed in
	//the string it points to will include duplicates so that probabilities match the passed in names
	map<char, string> charMap;
	//list of names passed in by user
	//used to generate the map
	vector<string> names;
	//the maximum length of generated names (will be truncated if they exceed this)
	int max_length;
	//character used as to signal end of a name
	const char END_OF_NAME = '0';
	//populates dictionary for word generation
	void populateMap();
	//generates one names using the character map
	string generateName(bool debug);
	//ensures name that has been generated passes tests (must have a vowel and must not be 1 character)
	bool checkName(string name);
	//prints map and other debug info to console
	void printDebug();
};

