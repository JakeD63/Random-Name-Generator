#include <iostream>
#include <string>
#include <vector>

#include "Generator.h"

using namespace std;

//function prototypes
vector<string> readFromFile();
vector<string> readFromUser();

int main() {
	vector<string> names, generatedNames;
	int selection, num;
	bool correctSelection = false;

	cout << "Make a selection from the menu below (enter its number)." << endl;
	cout << "1: Input names from file" << endl;
	cout << "2: Input names one at a time in the cmd prompt" << endl;
	cout << "3: Exit" << endl;

	while (!correctSelection) {
		cin >> selection;

		if (selection != 1 && selection != 2 && selection != 3) {
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

	generatedNames = nameGenerator.getNames(num);
	

}

vector<string> readFromFile() {
	vector<string> names;
	string file;
	cout << "Enter the name filepath: " << endl;
	cin >> file;
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