// Copyright 2021 Rithvik Doshi rithvik@bu.edu
// Pemdas 1.0-beta1.1

#include <iostream>
#include <string>
#include <math.h>

using std::cout;
using std::cin;
using std::string;
using std::ostream;
using std::stod;
using std::to_string;

string paren(string str);
string exp(string str);
string md(string str);
string as(string str);
bool isnumber(char c);

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
	bool out = false;
	if (((c >= '0' && c <= '9') || c == '.')) out = true;
	return out;
}

string eval(string str){
	while (!isnumber(str)){
		str = paren(str);
		str = exp(str);
		str = md(str);
		str = as(str);
	}
	return str;
}

string exp(string str){
	int prevnumstart = 0;
	int nextnumend = 0;
	int expindex = 0;
	while (find(str, '^') > 0){
		for (int i = 0; i < str.size(); i++){
			if (!isnumber(str.at(i))){
				if (str.at(i) == '^'){
					expindex = i;
					break;
				} else {
					prevnumstart = i+1;
				}
			}
		}
		nextnumend = expindex;
		for (int i = expindex+1; i < str.size(); i++){
			if (!isnumber(str.at(i))) {
				break;
			} else {
				nextnumend = i;
			}
		}
		double base = stod(str.substr(prevnumstart, expindex));
		double exponent = stod(str.substr(expindex+1, nextnumend));
		double result = pow(base, exponent);
		string s = to_string(result);
		str = str.substr(0, prevnumstart) + s + str.substr(nextnumend+1, str.length()-nextnumend-1);
	}
	return str;
}

string md(string str){
	int prevnumstart = 0;
	int nextnumend = 0;
	int opindex = 0;
	bool multordiv = true; // True for mult, False for div
	while (find(str, '*') > 0 || find(str, '/') > 0){
		for (int i = 0; i < str.size(); i++){
			if (!isnumber(str.at(i))){
				if (str.at(i) == '*' || str.at(i) == '/'){
					opindex = i;
					multordiv = (str.at(i) == '*')?true:false;
					break;
				} else {
					prevnumstart = i+1;
				}
			}
		}
		nextnumend = opindex;
		for (int i = opindex+1; i < str.size(); i++){
			if (!isnumber(str.at(i))) {
				break;
			} else {
				nextnumend = i;
			}
		}
		double first = stod(str.substr(prevnumstart, opindex));
		double second = stod(str.substr(opindex+1, nextnumend));
		double result = (multordiv)?first*second:first/second;
		string s = to_string(result);
		str = str.substr(0, prevnumstart) + s + str.substr(nextnumend+1, str.length()-nextnumend-1);
	}
	return str;
}

string as(string str){
	int prevnumstart = 0;
	int nextnumend = 0;
	int opindex = 0;
	bool addorsub = true; // True for add, False for sub
	while (find(str, '+') > 0 || find(str, '-') > 0){
		for (int i = 0; i < str.size(); i++){
			if (!isnumber(str.at(i))){
				if (str.at(i) == '+' || str.at(i) == '-'){
					opindex = i;
					addorsub = (str.at(i) == '+')?true:false;
					break;
				} else {
					prevnumstart = i+1;
				}
			}
		}
		nextnumend = opindex;
		for (int i = opindex+1; i < str.size(); i++){
			if (!isnumber(str.at(i))) {
				break;
			} else {
				nextnumend = i;
			}
		}
		double first = stod(str.substr(prevnumstart, opindex));
		double second = stod(str.substr(opindex+1, nextnumend));
		double result = (addorsub)?first+second:first-second;
		string s = to_string(result);
		str = str.substr(0, prevnumstart) + s + str.substr(nextnumend+1, str.length()-nextnumend-1);
	}
	return str;
}

string paren(string str){
	while (find(str, '(') > 0){
		int parbeg = find(str, '('); int parend = find(str, ')');
		string inpar = eval(str.substr(parbeg+1, parend-parbeg-1));
		str = str.substr(0, parbeg) + inpar + str.substr(parend+1, str.length()-parend-1);
	}
	return str;
}

int main() {
	string input;
	cout << "Welcome to basic integer calculator! Enter an expression to get started.\n";
	cout << "Error checking is currently not utilized so take care when writing expressions!\n";
	getline(cin, input);
	cout << input << " is evaluated to: " << eval(input) << "\n";
	return 0;
}
