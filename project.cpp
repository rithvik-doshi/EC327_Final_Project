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
    t.push_back( stod(s.substr(0, s.find(","))) );
    b.push_back( stod(s.substr(s.find(",") + 1)) );

  }

  Linear_Fit LbF(t, b);
  Exponential_Fit EbF(t, b);
  return 0;
}
