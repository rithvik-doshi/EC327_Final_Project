// Copyright 2021 Rithvik Doshi rithvik@bu.edu

#include <iostream>
#include <string>
#include <math.h>
// #define PEMDAS {'+', '-', '*', '/', '(', ')', '^', '\\'};
// #define NUMBER {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

using std::cout;
using std::cin;
using std::string;
using std::ostream;
using std::stod;
using std::to_string;

string paren(string str);
string exp(string str);

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
		str = exp(str);
	}
	return str;
}

string exp(string str){
	int prevnumstart = 0;
	int nextnumend = 0;
	int expindex = 0;
	for (int i = 0; i < str.size(); i++){
		if (!isnumber(str.at(i))){
			if (str.at(i) == '^'){
				expindex = i;
				i++;
				while (isnumber(str.at(i)) || i < str.size()) i++;
				nextnumend = --i;
				break;
			} else {
				prevnumstart = i+1;
			}
		}
	}
	cout << prevnumstart << expindex << nextnumend << "\n";
	double base = stod(str.substr(prevnumstart, expindex));
	cout << base << "\n";
	double exponent = stod(str.substr(expindex+1, nextnumend));
	cout << exponent << "\n";
	return to_string(pow(base, exponent));
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
	cout << input << " is evaluated to: " << eval(input) << "\n";

	// put eval here at some point


	return 0;
}
