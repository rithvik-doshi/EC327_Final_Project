// Copyright 2021 Rithvik Doshi rithvik@bu.edu
// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
// Copyright 2021 Johnson Yang johnsony@bu.edu

#include "Matrix.h"
#include <cmath>
#include <vector>

/* LEAST SQUARES COEFFICIENT

Ax = b

x = inv(A'A) * A' * b

*/

// 2x2 Matrix
struct Linear_Fit {
  // y = mt + c
  std::vector<double> x;
  Linear_Fit(std::vector<double>, std::vector<double>);
};

// 2x2 Matrix
struct Exponential_Fit {
  // y = Ne^kt to ln(y) = ln(N) + kt
  std::vector<double> x;
  double N, k;
  Exponential_Fit(std::vector<double>, std::vector<double>);
};

// 2x2 Matrix
struct Quadratic_Fit {
  // y = Et^2 + Ft + G

};

Linear_Fit::Linear_Fit(std::vector<double> t, std::vector<double> b) {
  Matrix A(t.size(),2);

  for (int i = 0 ; i < A.r; i++){
    A.set(i,0,t.at(i));
    A.set(i,1,1);
  }

  //std::cout << "MATRIX A:\n" << A << std::endl;
  Matrix A_T = A.transpose();
  //std::cout << "MATRIX A':\n" << A_T << std::endl;
  Matrix A_TA_I = (A_T * A).inverse();
  //std::cout << "Det A'A: " << (A_T * A).det() << std::endl; 
  //std::cout << "inv(A'A):\n" << A_TA_I << std::endl;
  std::vector<double> A_Tb = A_T * b;
  //std::cout << "A_Tb: \n" << A_Tb << std::endl;
  this -> x = A_TA_I * A_Tb;
}
 
Exponential_Fit::Exponential_Fit(std::vector<double> t, std::vector<double> b) {
  std::vector<std::vector<double>> data;

  Matrix A(t.size(),2);

  for (int i = 0 ; i < A.r; i++){
    A.set(i,0,t.at(i));
    A.set(i,1,1);
    b.at(i) = log(b.at(i));
  }

  //std::cout << "MATRIX A:\n" << A << std::endl;
  Matrix A_T = A.transpose();
  //std::cout << "MATRIX A':\n" << A_T << std::endl;
  Matrix A_TA_I = (A_T * A).inverse();
  //std::cout << "Det A'A: " << (A_T * A).det() << std::endl; 
  //std::cout << "inv(A'A):\n" << A_TA_I << std::endl;
  std::vector<double> A_Tb = A_T * b;
  //std::cout << "A_Tb: \n" << A_Tb << std::endl;
  this -> x = A_TA_I * A_Tb;

  this -> N = exp(x.at(1));
  this -> k = x.at(0);
}
 