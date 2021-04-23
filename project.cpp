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


int main(int argc, char** argv){
  Matrix A(9, 9);

  cout << A << '\n';

  Matrix B( { {2, 3, 2}, {4, 3, 2}, {1, 1, 1} } );
  cout << B << '\n';

  std::vector<double> v1 = {2, 3, 2};
  std::vector<double> v2 = {2, 3, 2};

  cout << "NORM SQUARED" << (v1 * v2) << '\n';

  std::vector<double> v3 = (B * v2);
  cout << v3 << '\n';

  A = B * B;
  cout << A << std::endl;

  Matrix C({{4,2},{6,0}});

  cout << C << std::endl;
  C.inverse(&C);
  cout << C << std::endl;

  return 0;
}
