// Copyright 2021 Rithvik Doshi rithvik@bu.edu
// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

#include <iostream>
#include <string>
#include <vector>
#include "Matrix.h"

using std::cout;
using std::ostream;
using std::string;
using std::to_string;

ostream& operator<<(ostream& os, Matrix& A) {
  string viewMatrix;
  for (int i = 0; i < A.r; i++) {
    for (int j = 0; j < A.c; j++){
      viewMatrix += to_string(A.at(i, j)) + '\t';
    }

    viewMatrix += '\n';
  }
  os << viewMatrix;
  return os;
}


int main(int argc, char** argv){
  Matrix A(5, 9);

  cout << A << '\n';
  Matrix B("2 3 4; 2 3 5");
  return 0;
}
