// Copyright 2021 Rithvik Doshi rithvik@bu.edu
// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
// Copyright 2021 Johnson Yang johnsony@bu.edu

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Best_Fit.h"

using std::cout;
using std::ostream;
using std::string;
using std::stod;
using std::to_string;


int main(int argc, char** argv) {
  std::ifstream inputFile;
  std::vector<string> rawData;
  std::map <double, double> data;

  inputFile.open("Data.csv");

  string line;
  while (std::getline(inputFile, line))
    rawData.push_back(line);
  inputFile.close(); // always close

  std::vector<double> t;
  std::vector<double> b;

  for (string s : rawData) {
    b.push_back( stod(s.substr(s.find(",") + 1)) );
    t.push_back( b.size() - 1 );
  }

  // DEMONSTRATIONS

  std::vector<double> v1 = {1, 2, 0};
  std::vector<double> v2 = {1, 0, 1};
  std::vector<double> v3 = {0, 2, 1};
  std::vector<double> v4 = {1, 2, 1};

  Matrix A({v1, v4});

  cout << "v1:\n" << v1 << std::endl;
  char c;
  std::cin >> c;

  cout << "NORM SQUARED: " << (v1 * v1) << std::endl;
  std::vector<double> vTemp = (A * v1);
  cout << "\nA * v1:\n" << vTemp << std::endl;

std::cin >> c;
  cout << "A:\n" << A << std::endl;

std::cin >> c;
  Matrix A_T = A.transpose();
  cout << "A':\n" << A_T << std::endl;

std::cin >> c; 
  Matrix A_TA = (A * A_T);
  cout << "AA':\n" << A_TA << std::endl;

std::cin >> c;
  double det = A_TA.det();
  cout << "\ndet(AA'): " << det << std::endl;

std::cin >> c;
  Matrix A_TA_i = A_TA.inverse();
  cout << "\ninv(AA'):\n" << A_TA_i << std::endl;



  Linear_Fit LbF(t, b);
  Exponential_Fit EbF(t, b);

std::cin >> c;
  cout << "b:\n" << b << std::endl;
std::cin >> c;
  std::cout << "\nLEAST SQUARES LINEAR:\ny = " << LbF.x.at(0) << "t + " << LbF.x.at(1) << std::endl;

std::cin >> c;  
  std::cout << "\nLEAST SQUARES EXPONENTIAL:\ny = " << EbF.N << "e^" << EbF.k << "t" << std::endl;
  return 0;
}
