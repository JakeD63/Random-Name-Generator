#include "Generator.h"
//Class definition of Generator.h

//The constructor will take a string of names to add to the map
//as well as the max size of the generated names
Generator::Generator(vector<string> names, int max_length) {
	//copy list of names into object for use
	this->names = names;
	//copy over max size
	this->max_length = max_length;
	//call the populate routine to generate our map
	populateMap();
	//seed the randomizer
	srand(time(NULL));
}

//Populates map with charactars as keys. This map has each character from
//all input names as keys, and the string at those keys are all possible letters
//that follow that character from input names. A 0 represents the end of a name
//EXAMPLE: input names - Jake, Daniel, Bill
//j - a
//a - kn
//k - e
//e - 0l
//d - a
//n - i
//i - el
//l - 0l
//B - i
void Generator::populateMap() {
	char next, last; //character after current to be added to value, last character in name

	//loop through list of names adding the characters to 
	//the probability map
	for (string input : this->names) {
		//loop through each character of the string (except last)
		for (int i = 0; i < input.length() - 1; i++) {
			next = input.at(i + 1);
			next = tolower(next);
			//add the character to the map
			//duplicates are still added (needed for probabilities)
			this->charMap[tolower(input.at(i))] += next;
		}
		//now we need to handle the end of the name (use 0 as placeholder)
		last = input.at(input.length() - 1);
		this->charMap[last] += this->END_OF_NAME;
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
		//if the name is not a good one (i.e no vowels or too short we generate a new one
		while (!checkName(currentName)) {
			currentName = this->generateName();
		}
		//push back name to list, keeping in sorted order
		vector<string>::iterator it = lower_bound(generatedNames.begin(), generatedNames.end(), currentName);
		//check for duplicates
		if (it == generatedNames.end() || *it != currentName) {
			generatedNames.insert(it, currentName);
		}
		//if there was a duplicate, rerun current loop and get new name
		else
			i--;
	}

	//return list to user
	return generatedNames;
}

//generate a random name using the map we generated
string Generator::generateName() {
	vector<char> startingChars; //holds first letters of passed in words, we only start with those
	string name, next;
	char cur; //current character to add to name

	//get all the characters input names started with
	//we do this so that names begin with only those characters
	//this way they have a good chance of taking a path that makes the most sense
	for (string s : this->names)
		startingChars.push_back(tolower(s.at(0)));

	int size = startingChars.size();
	//first, we pick our starting letter, must be one in our map
	cur = startingChars.at(rand() % size);

	//while the next character is not the end of a name
	while (cur != this->END_OF_NAME) {
		//add character to name
		name += cur;
		//if we have passed max length, break
		if (name.length() >= max_length)
			break;
		//get the next string of valid characters that come after current character
		next = charMap[cur];
		//now, get random char from next string
		cur = next.at(rand() % (next.length()));
	}
	
	//make first letter in name uppercase
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

