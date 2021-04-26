// Copyright 2021 Rithvik Doshi rithvik@bu.edu
// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
// Copyright 2021 Johnson Yang johnsony@bu.edu

#include <iostream>
#include <string>
#include <vector>
#include "Best_Fit.h"

using std::cout;
using std::ostream;
using std::string;
using std::to_string;


int main(int argc, char** argv) {
  std::vector<double> t {-3, -2 , 0, 2, 2.5, 3};
  std::vector<double> b {0.5, 3 , 6, 7, 10, 30};

  // Matrix B( { {3, 0, 1, 0}, {1, 0, 2, 1}, {0, 1, 0, 1}, {1, 0, 2, -2}});
  // std::vector<double> v1 = {2, 3, 2};
  // std::vector<double> v2 = {2, 3, 2};

  // cout << "NORM SQUARED" << (v1 * v2) << '\n';

  // std::vector<double> v3 = (B * v2);
  // cout << v3 << '\n';

  // A = B * B;
  // cout << A << std::endl;

  // Matrix C({{4,2},{6,0}});

  // cout << C << std::endl;
  // C.inverse(&C);
  // cout << C << std::endl;

  // cout << "MATRIX A:\n" << A << std::endl;
  // Matrix A_T = A.transpose();
  // cout << "MATRIX A':\n" << A_T << std::endl;
  // Matrix A_TA_I = (A_T * A).inverse();
  // cout << "Det A'A: " << (A_T * A).det() << std::endl; 
  // cout << "inv(A'A):\n" << A_TA_I << std::endl;
  // std::vector<double> A_Tb = A_T * b;
  // cout << "A_Tb: \n" << A_Tb << std::endl;
  // std::vector<double> x = A_TA_I * A_Tb;
  // cout << "inv(A'A)A'b: \n" <<  x << std::endl;

  Linear_Fit LbF(t, b);
  Exponential_Fit EbF(t, b);
  return 0;
}
