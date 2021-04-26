// Copyright 2021 Rithvik Doshi rithvik@bu.edu
// Copyright 2021 Muhammed Abdalla muhabda@bu.edu
// Copyright 2021 Johnson Yang johnsony@bu.edu

#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::to_string;

typedef std::vector< std::vector<double> > matrix;

class Matrix {
  protected:
    matrix A;
  public:
    int r, c;
    Matrix(matrix);
    Matrix(int, int); // init rows and columns; empty matrix
    std::vector<double> row(int);
    std::vector<double> col(int);
    double at(int, int);
    void set(int, int, double);
    // MATRIX FUNCTIONS
    Matrix transpose();
    // ONLY SQUARE MATRICES
    Matrix inverse();
    double det();
    double cofactor(double);

};

// OVERLOADING COMMANDS: MATRIX PRINT
std::ostream& operator<<(std::ostream& os, Matrix& A) {
  string viewMatrix;
  for (int i = 0; i < A.r; i++){
    for (int j = 0; j < A.c; j++)
      viewMatrix += to_string(A.at(i, j)) + ' ';
    viewMatrix += '\n';
  }
  os << viewMatrix;
  return os;
}

// OVERLOADING COMMANDS: VECTOR PRINT (AS COLUMNS)
std::ostream& operator<<(std::ostream& os, std::vector<double>& vec) {
  string viewVector;
  for (auto i : vec)
    viewVector += to_string(i) + '\n';
  os << viewVector;
  return os;
}

// SCALAR PRODUCT VECTORS
std::vector<double> operator*(std::vector<double> vec, double c) {
  std::vector<double> b;
  for (int i = 0; i < vec.size(); i++)
    b.push_back(vec.at(i) * c);
  return b;
}

std::vector<double> operator*(double c, std::vector<double> vec) {
  std::vector<double> b;
  for (int i = 0; i < vec.size(); i++)
    b.push_back(vec.at(i) * c);
  return b;
}

// SCALAR PRODUCT MATRICES
Matrix operator*(Matrix M, double c) {
  for (int i = 0; i < M.r; i++)
    for (int j = 0; j < M.c; j++)
      M.set(i,j, M.at(i,j) * c);
  return M;
}

Matrix operator*(double c, Matrix M) {
  for (int i = 0; i < M.r; i++)
    for (int j = 0; j < M.c; j++)
      M.set(i,j, M.at(i,j) * c);
  return M;
}

// DOT PRODUCT
double operator*(std::vector<double> vec1, std::vector<double> vec2) {
  double dotProduct;
  
  if (vec1.size() != vec2.size())
    std::cerr << "Dimension Mismatch\n";
  for (int i = 0; i < vec1.size(); i++)
    dotProduct += vec1.at(i) * vec2.at(i);

  return dotProduct;
}

// MATRIX MULTIPLICATION VECTOR
std::vector<double> operator*(Matrix& M, std::vector<double>& vec) {
  std::vector<double> b;
  if (M.c != vec.size())
    std::cerr << "Dimension Mismatch\n";
 for (int i = 0; i < M.r; i++)
   b.push_back(M.row(i) * vec);
  return b;
}

// MATRIX MULTIPLICATION
Matrix operator*(Matrix& M, Matrix& N) {
  Matrix m(M.r,N.c);
  if (M.c != N.r)
    std::cerr << "Dimension Mismatch\n";
  for (int i = 0; i < m.r; i++)
    for (int j = 0; j < m.c; j++) {
      double dotProd = M.row(i) * N.col(j);
      m.set(i,j,dotProd);
    }
  return m;
}

// MATRIX CONSTRUCTOR (VECTOR OF VECTORS)
Matrix::Matrix(matrix A) {
  this -> r = A.size();
  this -> c = A.at(0).size();
  this -> A = A;
}

// MATRIX CONSTRUCTOR (INIT BY SIZE)
Matrix::Matrix(int rows, int columns) {
  this -> r = rows;
  this -> c = columns;
  std::vector<double> zeros(columns, 0); // these are your rows vectors
  for (int i = 0; i < rows; i++) 
    A.push_back(zeros);
}

// GET COLUMN OF A MATRIX
std::vector<double> Matrix::col(int n) {
  std::vector<double> colVec;
  for (std::vector<double> row : A)
    colVec.push_back(row.at(n));
  return colVec;
}

// GET ROW OF A MATRIX
std::vector<double> Matrix::row(int n) {
  return A.at(n);
}

// GET VALUE AT ROW, COLUMN POSITION OF A MATRIX
double Matrix::at(int r, int c) {
  return A.at(r).at(c);
}

// SET VALUE AT ROW, COLUMN POSITION OF A MATRIX
void Matrix::set(int r, int c, double val) {
  A.at(r).at(c) = val;
}

// Complexity (n-1)^2
Matrix cofactorExpansion(Matrix A, int row, int col) {
  Matrix B(A.r-1, A.c-1);
  int B_row, B_col;
  B_row = B_col = 0;
  for (int i = 0; i < A.r; i++) {

    if (i == row)
      continue;
    B_col = 0;
    for (int j = 0; j < A.c; j++) {

      if (j == col)
        continue;
      B.set(B_row, B_col, A.at(i,j));
      B_col++;
    }

    B_row++;
  }
  return B;
}

// Complexity (!n)^2
double Matrix::cofactor(double mult) {
  std::vector<int> multipliers;
  int rowSign, colSign, multSign;
  double coFactor,tempDet,detSum;
  coFactor = rowSign = colSign = multSign = 1;
  tempDet = detSum = 0;

  for (int i = 0; i < this -> r; i++) {
    colSign = 1;
    for (int j = 0; j < this -> c; j++) { // when its a 3x3 it will make 2x2 Co-M's
      multSign = rowSign * colSign;

      coFactor = multSign * (this -> at(i,j));
      multipliers.push_back(coFactor);
      

      Matrix C = cofactorExpansion(this -> A, i, j);
      /*
      std::cout << "\nCOFACTOR A" << multipliers.size() 
        << "\ncofactor: " << multipliers.at(multipliers.size()-1) << std::endl 
        << C << std::endl;
      */
      if (C.r > 2) {
        tempDet = C.cofactor(coFactor);
        detSum += tempDet; // sums all the nxn's from their 2x2 sums
        std::cout << "Cofactor: " << mult << std::endl;
        std::cout << C.r << "x" << C.r << "[ DET CO-M A" << multipliers.size() << "]: ";
        std::cout << tempDet << std::endl;
        std::cout << "\n---------------------------------------\n";
      } else if (C.r == 2) {
        tempDet = C.det() * coFactor;
        std::cout << C.det() << std::endl;
        detSum += tempDet; // sums all the 2x2 dets for 3x3
        std::cout << "Cofactor: " << coFactor << "\t";
        std::cout << "2x2 DET CO-M A" << multipliers.size() << ": ";
        std::cout << tempDet << std::endl;
      }
      colSign *= -1;
    }
    rowSign *= -1;
  }
  std::cout << "Determinant sum: " << detSum << std::endl;
  return detSum;
}

double Matrix::det() {
  double det = 0;
  if (this -> r != this -> c)
    std::cerr << "Matrix not square";
  if (this -> r != this -> c)
    std::cerr << "Matrix not 2x2";
  if (this -> r == 2)
    det = ( (this -> at(0,0)) * (this -> at(1,1)) ) - 
          ( (this -> at(1,0)) * (this -> at(0,1)) );
  return det;
}


Matrix Matrix::inverse() {
  Matrix newMatrix({
          {   this -> at(1,1), -(this -> at(1,0))},
          { -(this -> at(0,1)),  this -> at(0,0)}
  });

  return (1/(this -> det())) * newMatrix;
}

Matrix Matrix::transpose() {
  // Cols A become Rows of A
  Matrix newMatrix(this -> c, this -> r);

  for (int i = 0; i < this -> c; i++) {
    for (int j = 0; j < this -> r; j++) {
      newMatrix.set(i,j,this -> at(j,i));
    }
  }

  return newMatrix;
}
