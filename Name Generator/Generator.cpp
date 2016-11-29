#include "Generator.h"

//The constructor will take a string of names to add to the map
Generator::Generator(vector<string> names) {
	//copy list of names into object for use
	this->names = names;
	//call the populate routine to generate our map
	populateMap();
}


//This function returns a list of generated names the size of the number passed in
vector<string> Generator::getNames(int number) {
	vector<string> generatedNames;
	for (int i = 0; i < number; i++) {
		generatedNames.push_back(this->generateName());
	}
	return generatedNames;
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

//generate a random name using the map we generated
string Generator::generateName() {
	srand(time(NULL));
	string name, next;
	char cur;
	int size = listOfKeys.size() - 1; //need -1 to avoid off by 1 error
	//first, we pick our starting letter, must be one in our map
	cur = listOfKeys.at(rand() % size);


	//0 is our end of word
	while (cur != '0') {
		name += cur;
		next = charMap[cur];
		//now, get random char from next string
		cur = next.at(rand() % (next.length() - 1)); //need -1 to avoid off by one
	}
	
	//make first char in name uppercase
	name.at(0) = toupper(name.at(0));
	cout << "Name Generated: " << name << endl;
	return name;
}


