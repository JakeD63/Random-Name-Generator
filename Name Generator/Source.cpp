#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Generator.h"

using namespace std;

//function prototypes
vector<string> readFromFile(int& max_length);
vector<string> readFromUser(int& max_length);
void outputNames(vector<string> generatedNames, char file);
int getNum();
char getIO();
bool hasVowel(string name);

int main() {
	vector<string> names, generatedNames; //stores user input names and names generated by the markov chain
	int selection, num, max_length = 0; //menu choice, number of words to generate, max_length of the generated words
	bool correctSelection = false; //used in input validation
	char file; //y/n for file or output to console

	//Output welcome message and selection menu
	cout << "Welcome to the name generator. Names will be generated based on your input.";
	cout << "Generated names will only be as long as the longest name from your input." << endl << endl;
	cout << "Make a selection from the menu below (enter its number)." << endl;
	cout << "1: Input names from file" << endl;
	cout << "2: Input names one at a time in the cmd prompt" << endl;
	cout << "3: Exit" << endl;

	//Read menu selection from user
	while (!correctSelection) {
		cin >> selection;
		if (cin.fail()) {
			cout << "Please enter only an integer for the menu selection" << endl;
			return 0;
		}
		else if (selection != 1 && selection != 2 && selection != 3) {
			cout << "Please input a 1, 2, or 3 for your selection" << endl;
		}
		else {
			correctSelection = true;
		}
	}

	//Take input from either a file or user input
	//depending on user selection
	switch (selection) {
	case 1: 
		//read input names from file
		names = readFromFile(max_length);
		break;
	case 2:
		//read input names from the console
		names = readFromUser(max_length);
		break;
	case 3:
		//exit the program
		return 0;
	default:
		//This is not the error statement you should see, but if this is reached something went horribly wrong.
		cout << "You have entered an incorrect menu item. Please run program again.";
		return 0;
	}

	//if they did not enter any names, or all names had no vowels
	//output error message and exit program
	if (names.empty()) {
		cout << "List of names empty, exiting." << endl;
		return 0;
	}

	//construct name generator object with input names and 
	//length of longest input word
	Generator nameGenerator(names, max_length);

	//clear cin stream for input
	cin.clear();
	//get the number of words they want to generate
	num = getNum();
	//get whether to output generated names to file or console
	file = getIO();

	//generate names and store into list
	generatedNames = nameGenerator.getNames(num);
	//output the names to either a file or the console
	outputNames(generatedNames, file);
	//end program
	return 0;
}

//Reads input names from a provided file
//also keeps track of the length of the longest word
vector<string> readFromFile(int& max_length) {
	vector<string> names; //container to return names in
	ifstream fin; //input stream to read file
	string file, nextName; //filepath, string to hold name read in
	
	//tell user rules about names being read in (names must have at least one vowel or they will be ignored)
	cout << "Ensure the file with the names contains only one name per line (no special characters, words without vowels will be ignored)" << endl;
	cout << "File name and path: ";
	//get the filepath from user
	cin >> file;
	//ensure they entered a single string for the filepath
	if (cin.fail()) {
		cout << "Please enter only the filepath. Try again.";
		exit(0);
	}
	//open the file they entered and check for success
	fin.open(file);
	if (!fin) {
		cout << "Failed to open file, please try again.";
		exit(0);
	}
	//read in names and store in vector until the end of the file
	while (fin >> nextName) {
		//keep track of length of longest word
		if (max_length < nextName.length())
			max_length = nextName.length();
		//ensure word has at least one vowel
		if(hasVowel(nextName))
			names.push_back(nextName);
	}
	//close stream and return vector of names
	fin.close();
	return names;
}

//gets a list of names from console input from the user
//also keeps track of the length of the longest word
vector<string> readFromUser(int& max_length) {
	vector<string> names; //vector of input names
	string input; //current name user has input
	//output usage statemtn
	cout << "Enter one name at a time, followed by the enter key. When you are done, enter CTRL + Z (words without vowels will be ignored)" << endl;
	//get first input
	cin >> input;
	//loop until ctrl+z (eof)
	while (!cin.eof()) {
		//keep track of max word length
		if (max_length < input.length())
			max_length = input.length();
		//ensure the word has at least one vowel
		if(hasVowel(input))
			names.push_back(input);
		cin >> input;
	}
	//return vector of names
	return names;
}

//get the number of words to generate from user
int getNum() {
	int num; //number of words to generate
	bool correctSelection; //used to validate user input
	//ask for number of words to generate
	cout << "How many names would you like to generate?" << endl;
	//get user input, making sure they entered only one number
	correctSelection = false;
	while (!correctSelection) {
		cin >> num;
		if (cin.fail()) {
			cout << "Please enter only a a single number. Exiting program." << endl;
			return 0;
		}
		else {
			correctSelection = true;
		}
	}
	//return the number the user entered
	return num;
}

//asks user whether they want the generated names to be 
//output in a file or to the console
char getIO() {
	char file; //stores y/n for user selection
	bool correctSelection; //used to validate input
	//output prompt to user
	cout << "Do you want the output in a file? (y/n)" << endl;
	//get user input, making sure they only entered a single character
	correctSelection = false;
	while (!correctSelection) {
		cin >> file;
		if (cin.fail()) {
			cout << "Please enter only a single character for your response." << endl;
			cin.clear();
			cin.ignore();
		}
		else if (file != 'y' && file != 'n') {
			cout << "Please enter only y or n." << endl;
		}
		else {
			correctSelection = true;
		}
	}
	//return user choice
	return file;
}

//output the generated names
//either to a file or to the console (depending on value of file paramater)
void outputNames(vector<string> generatedNames, char file) {
	ofstream fout; //used if user selects output to file
	//if they chose output to console
	if (file == 'n') {
		//output all generated names to console
		for (string s : generatedNames) {
			cout << s << endl;
		}
	}
	//if they wanted a file output
	else {
		//open file for output (file will be created if it does not exist)
		//file is located in program directory
		fout.open("Generated Names.txt");
		//output all generated names to file
		for (string s : generatedNames) {
			fout << s << endl;
		}
	}
}

//helper function, returns whether a string contains a vowel or not
bool hasVowel(string name) {
	//we treat y as a vowel since in names you can have a y
	//and no other vowels and it is valid
	if (name.find_first_of("aeiouy") == string::npos) {
		return false;
	}
	return true;
}