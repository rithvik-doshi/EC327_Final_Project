// Copyright 2021 Rithvik Doshi rithvik@bu.edu
// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

#include <vector>
#include <string>

struct Matrix {
    std::vector< std::vector<int> > A;
    int r, c;
    Matrix(int, int); // init rows and columns; empty matrix
    Matrix(std::string);
    int at(int, int);
};

Matrix::Matrix(int rows, int columns) {
  this -> r = rows;
  this -> c = columns;
  std::vector<int> zeros(columns, 0); // these are your rows vectors
  for (int i = 0; i < rows; i++) 
    A.push_back(zeros);
}

// params m is a matrix in string format, similar to matlab
// 2x3 matrices look like: [2 3 4; 4 7 5]
// each element in a row seperated by a space 
// each row seperated by a semi-colon
Matrix::Matrix(std::string m) {
  //for (int i = 0; i < m.size(); i++){
  if (m.find(";") == std::string::npos) {
    this -> r = 1;
    this -> c = m.size() - (m.size()/2 - 1);
  } else {
    int tally, semiC_idx;
    tally = semiC_idx = 0;
    for (int i = 0; i < m.size(); i++) {
      if (semiC_idx = m.find(";", semiC_idx) != std::string::npos) {
        tally++;
        i = semiC_idx + 1;
      }
    }
  }
  //

}

int Matrix::at(int r, int c) {
  return A.at(r).at(c);
}
