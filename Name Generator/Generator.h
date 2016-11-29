#pragma once

#include <string>
#include <map>
#include <vector>
#include <time.h>

using namespace std;

class Generator
{

//class member functions
public:
	Generator(vector<string> names, int max_size);
	vector<string> getNames(int number);

//class member variables
private:
	//maps characters to a string of characters that follow in the list of names passed in
	//the string it points to will include duplicates so that probabilities match the passed in names
	map<char, string> charMap;
	//list of names passed in by user
	//used to generate the map
	vector<string> names;
	//the maximum size of generated names (will be truncated if they exceed this)
	int max_size;

	void populateMap();
	string generateName();
	bool checkName(string name);
};

