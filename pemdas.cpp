// Copyright 2021 Rithvik Doshi rithvik@bu.edu

#include <iostream>
#include <string>
#define PEMDAS {'+', '-', '*', '/', '(', ')', '^', '\\'};
#define NUMBER {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

using std::cout;
using std::cin;
using std::string;
using std::ostream;

string paren(string str);

int find(string str, char c){
	for (int i = 0; i < str.size(); i++){
		if (str.at(i) == c) return i;
	}
	return -1;
}

bool isnumber(string str){
	bool out = true;
	for (char i : str){
		out = isnumber(i);
		if (!out) return out;
	}
	return out;
}

bool isnumber(char c){
	bool out = true;
	if (!(c >= '0' && c <= '9')) out = false;
	return out;
}

string eval(string str){
	while (!isnumber(str)){
		str = paren(str);

	}
}

string exp(string str){
	int prevnumstart = 0;
	int nextnumend = 0;
	int expindex = 0;
	for (char i : str){
		if (!isnumber(i)){
			if (i == '^'){
				expindex = find(str, '^');
				
			} else {
				prevnumstart = find(str, i);
			}
		}
	}
}

string paren(string str){
	while (find(str, '(') > 0){
		int parbeg = find(str, '('); int parend = find(str, ')');
		string inpar = eval(str.substr(parbeg+1, parend-parbeg-1));
		str = str.substr(0, parbeg) + inpar + str.substr(parend+1, str.length()-parend-1);
		cout << str << "\n";
	}
	return str;
}

int main() {
	string input;
	cout << "Welcome to basic integer calculator! Enter an expression to get started.\n";
	cout << "Error checking is currently not utilized so take care when writing expressions!\n";
	getline(cin, input);
	cout << input << " is evaluated to: \n";

	// Parentheses

	// while (find(input, '(') > 0){
	// 	int parbeg = find(input, '('); int parend = find(input, ')');
	// 	string inpar = input.substr(parbeg+1, parend-parbeg-1);
	// 	input = input.substr(0, parbeg) + inpar + input.substr(parend+1, input.length()-parend-1);
	// 	cout << input << "\n";
	// }


	return 0;
}
