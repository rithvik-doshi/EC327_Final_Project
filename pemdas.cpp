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

bool isnumber(string str){
	bool out = true;
	for (char i : str){
		if (!(i >= '0' && i <= '9')) out = false;
	}
	return out;
}

string eval(string str){
	while (!isnumber(str)){
		
	}
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
		string inpar = input.substr(parbeg+1, parend-parbeg-1);
		input = input.substr(0, parbeg) + inpar + input.substr(parend+1, input.length()-parend-1);
		cout << input << "\n";
	}


	return 0;
}
