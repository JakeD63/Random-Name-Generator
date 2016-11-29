#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Generator.h"

using namespace std;

//function prototypes
vector<string> readFromFile(int& max_size);
vector<string> readFromUser(int& max_size);
bool hasVowel(string name);

int main() {
	vector<string> names, generatedNames;
	ofstream fout;
	int selection, num, max_size = 0;
	bool correctSelection = false;
	char file;
	cout << "Welcome to the name generator. Names will be generated based on your input.";
	cout << "Generated names will only be as long as the longest name from your input." << endl << endl;
	cout << "Make a selection from the menu below (enter its number)." << endl;
	cout << "1: Input names from file" << endl;
	cout << "2: Input names one at a time in the cmd prompt" << endl;
	cout << "3: Exit" << endl;

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


	switch (selection) {
	case 1: 
		names = readFromFile(max_size);
		break;
	case 2:
		names = readFromUser(max_size);
		break;
	case 3:
		cout << "3";
		return 0;
	default:
		//This is not the error statement you should see, but if this is reached something went horribly wrong.
		cout << "You have entered an incorrect menu item. Please run program again.";
		return 0;
	}

	if (names.empty()) {
		cout << "List of names empty, exiting." << endl;
		return 0;
	}
	Generator nameGenerator(names, max_size);

	cin.clear();

	cout << "How many names would you like to generate?" << endl;
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

	cout << "Do you want the output in a file? (y/n)" << endl;
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

	generatedNames = nameGenerator.getNames(num);
	//if they did not want a file, output to console
	if (file == 'n') {
		for (string s : generatedNames) {
			cout << s << endl;
		}
	}
	//if they wanted a file output
	else {
		fout.open("Generated Names.txt");
		for (string s : generatedNames) {
			fout << s << endl;
		}
	}

}

vector<string> readFromFile(int& max_size) {
	vector<string> names;
	ifstream fin;
	string file, nextName;
	cout << "Ensure the file with the names contains only one name per line (no special characters, words without vowels will be ignored)" << endl;
	cout << "File name and path: ";
	cin >> file;
	if (cin.fail()) {
		cout << "Please enter only the filepath. Try again.";
		exit(0);
	}
	fin.open(file);
	if (!fin) {
		cout << "Failed to open file, please try again.";
		exit(0);
	}

	while (fin >> nextName) {
		if (max_size < nextName.length())
			max_size = nextName.length();
		if(hasVowel(nextName))
			names.push_back(nextName);
	}
	
	fin.close();
	return names;
}

vector<string> readFromUser(int& max_size) {
	vector<string> names;
	string input;
	cout << "Enter one name at a time, followed by the enter key. When you are done, enter CTRL + Z (words without vowels will be ignored)" << endl;
	cin >> input;
	while (!cin.eof()) {
		//keep track of max word size
		if (max_size < input.length())
			max_size = input.length();
		if(hasVowel(input))
			names.push_back(input);
		cin >> input;
	}

	return names;
}

bool hasVowel(string name) {
	if (name.find_first_of("aeiouy") == string::npos) {
		return false;
	}
	return true;
}