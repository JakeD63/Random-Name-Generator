#include "Generator.h"

//The constructor will take a string of names to add to the map
//as well as the max size of the generated names
Generator::Generator(vector<string> names, int max_size) {
	//copy list of names into object for use
	this->names = names;
	//copy over max size
	this->max_size = max_size;
	//call the populate routine to generate our map
	populateMap();
	//seed the randomizer
	srand(time(NULL));
}


void Generator::populateMap() {
	char next, last;

	//loop through list of names adding the characters to 
	//the probability map
	for (string input : this->names) {
		//loop through each character of the string
		for (int i = 0; i < input.length() - 1; i++) {
			next = input.at(i + 1);
			next = tolower(next);
			//add the character to the map
			//duplicates are still added (needed for probabilities)
			this->charMap[tolower(input.at(i))] += next;
		}
		//now we need to handle the end of the name (use 0 as placeholder)
		last = input.at(input.length() - 1);
		this->charMap[last] += '0';
	}
	//finally, we need to generate a list of keys in our map
	//used to pick first letter of a generated name
	for (map<char, string>::iterator i = charMap.begin(); i != charMap.end(); i++) {
		this->listOfKeys.push_back(i->first);
	}
}

//This function returns a list of generated names the size of the number passed in
vector<string> Generator::getNames(int number) {
	vector<string> generatedNames;
	bool validName = false;
	string currentName;
	for (int i = 0; i < number; i++) {
		//generate a new name and add to list
		currentName = this->generateName();
		//if the name is not a good one (i.e no vowels or too short)
		//we generate a new one
		while (!checkName(currentName)) {
			currentName = this->generateName();
		}
		generatedNames.push_back(currentName);
	}
	return generatedNames;
}

//generate a random name using the map we generated
string Generator::generateName() {
	string name, next;
	char cur;
	int size = listOfKeys.size();
	//first, we pick our starting letter, must be one in our map
	cur = listOfKeys.at(rand() % size);


	//0 is our end of word
	while (cur != '0') {
		name += cur;
		if (name.length() >= max_size)
			break;
		next = charMap[cur];
		//now, get random char from next string
		cur = next.at(rand() % (next.length()));
	}
	
	//make first char in name uppercase
	name.at(0) = toupper(name.at(0));
	return name;
}

//This function ensures names make some sense
//runs the generated name through some tests
//if the name fails, return false
bool Generator::checkName(string name) {
	if (name.length() < 2) {
		return false;
	}

	//check that name has at least one vowel (a, e, i, o, u or y)
	//NOTE: technically, y is a vowel sometimes, but for names it is irrelevant
	//(because y is a vowel if it is the only one from the above list in the word)
	if (name.find_first_of("aeiouy") == string::npos) {
		return false;
	}

	return true;
	
}

