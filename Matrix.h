// Copyright 2021 Rithvik Doshi rithvik@bu.edu
// Copyright 2021 Muhammed Abdalla muhabda@bu.edu

#include <vector>
#include <string>
using std::string;
using std::to_string;

typedef std::vector< std::vector<double> > matrix;

class Matrix {
  private:
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
    void transpose(Matrix*);
    // ONLY SQUARE MATRICES
    void inverse(Matrix*);
    double det(Matrix);

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
  if (M.row(0).size() != vec.size())
    std::cerr << "Dimension Mismatch\n";
   for (int i = 0; i < vec.size(); i++)
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


double findDeterminant(Matrix A) {
  double det = 0;
  if (A.r != A.c)
    std::cerr << "Matrix not square";
  if (A.r == 2)
    det = (A.at(0,0) * A.at(1,1)) - (A.at(1,0) * A.at(0,1));
  return det;
}


void Matrix::inverse(Matrix* m) {
  // Rule: get down to 2x2 then find adjecent matrix and multiply by det of the 2x2
  // [a b; c d] -> (ad - bc)^-1 * [d -c; -b a]
  Matrix newMatrix({ {(*m).at(1,1), -(*m).at(1,0)}, {-(*m).at(0,1), (*m).at(0,0)} });
  *m = findDeterminant(*m) * newMatrix;
}


