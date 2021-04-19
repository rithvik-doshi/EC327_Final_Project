// Copyright 2021 Rithvik Doshi rithvik@bu.edu

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::ostream;

class contains_at{
	public:

		bool contains;
		int index;

		contains_at(){
			this->contains = false;
			this->index = 0;
		}

		static contains_at find(string str, char c){
			contains_at out = contains_at();
			for (int i = 0; i < str.size(); i++){
				if (str.at(i) == c){
					out.contains = true; out.index = i;
				}
			}
			out.contains = false; out.index = -1;
			return out;
		}
};

ostream& operator<<(ostream& os, const contains_at& x){
	os << x.contains << " " << x.index;
	return os;
}

int main() {
	string input;
	cout << "Welcome to basic calculator! Enter an expression to get started.\n";
	getline(cin, input);
	cout << input << " is evaluated to: \n";

	cout << contains_at() << "\n";

	contains_at begpar = contains_at::find(input, '(');

	cout << begpar.index << "\n";

	while (begpar.index > 0){
		cout << begpar << "\n";
		begpar = contains_at::find(input.substr(begpar.index), '(');
	}


	return 0;
}