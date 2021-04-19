// Copyright 2021 Rithvik Doshi rithvik@bu.edu

#include <iostream>
#include <string>
#define PEMDAS {'+', '-', '*', '/', '(', ')', '^', '\\'};
#define NUMBER {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

using std::cout;
using std::cin;
using std::string;
using std::ostream;

int find(string str, char c){
	for (int i = 0; i < str.size(); i++){
		if (str.at(i) == c) return i;
	}
	return -1;
}

string eval(string str){
	while
}

int main() {
	string input;
	cout << "Welcome to basic integer calculator! Enter an expression to get started.\n";
	cout << "Error checking is currently not utilized so take care when writing expressions!\n";
	getline(cin, input);
	cout << input << " is evaluated to: \n";

	// Parentheses

	while (find(input, '(') > 0){
		int parbeg = find(input, '('); int parend = find(input, ')');
		input = input.substr(0, parbeg) + input.substr(parbeg+1, parend-parbeg-1) + input.substr(parend+1, input.length()-parend-1);
		cout << input << "\n";
	}


	return 0;
}