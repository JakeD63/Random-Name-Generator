#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Generator.h"

using namespace std;

//function prototypes
vector<string> readFromFile();
vector<string> readFromUser();

int main() {
	vector<string> names, generatedNames;
	ofstream fout;
	int selection, num;
	bool correctSelection = false;
	char file;

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
		names = readFromFile();
		break;
	case 2:
		names = readFromUser();
		break;
	case 3:
		cout << "3";
		return 0;
	default:
		//This is not the error statement you should see, but if this is reached something went horribly wrong.
		cout << "You have entered an incorrect menu item. Please run program again.";
		return 0;
	}

	Generator nameGenerator(names);

	cin.clear();

	cout << "How many names would you like to generate?" << endl;
	cin >> num;

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

vector<string> readFromFile() {
	vector<string> names;
	ifstream fin;
	string file, nextName;
	cout << "Enter the name filepath: " << endl;
	cout << "Ensure the file with the names contains only one name per line (no special characters)" << endl;
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
		names.push_back(nextName);
	}
	
	fin.close();
	return names;
}

vector<string> readFromUser() {
	vector<string> names;
	string input;
	cout << "Enter one name at a time, followed by the enter key. When you are done, enter CTRL + Z" << endl;
	cin >> input;
	while (!cin.eof()) {
		names.push_back(input);
		cin >> input;
	}

	return names;
}