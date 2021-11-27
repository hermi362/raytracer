#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <initializer_list>

#include "tuple.h"


// implements a square (NxN) matrix
class Matrix {
  private:
    int N;          // matrix size (N*N)
    float* mData;   // matrix values as array
    float at(int i) const { return mData[i]; } // get matrix value at array index i
  public:
    Matrix(int dim);  // create zero-filled matrix of given dim
    Matrix(int dim, std::initializer_list<float> values); // initialize from list of floats
    Matrix() : Matrix(1) {} // override the default constructor. good practise.

    Matrix(const Matrix& m);              // copy constructor
    Matrix& operator=(const Matrix& rhs); // copy assignment

    Matrix(Matrix&& m) noexcept; // move constructor
    Matrix& operator=(Matrix&& m) noexcept; // move assignment
    
    ~Matrix();

    int dimension() const { return N; } // get matrix size (N)
    float at(int row, int col) const;  // get single matrix value at (row,col)

    bool operator==(const Matrix& rhs) const;  // test for equality.
    bool operator!=(Matrix& rhs) const { return !operator==(rhs); }

    void setValue(int row, int col, float value);

    std::string toString() const;

    Matrix transpose() const;  // return transpose as new Matrix

    float determinant() const; 
    float cofactor(int row, int col) const; 
    float minor(int row, int col) const; 
    Matrix submatrix(int row, int col) const;

    bool isInvertible() const;
    Matrix inverse() const;  // return inverse as new Matrix
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs); // multiplication
Tuple operator*(const Matrix& lhs, const Tuple& rhs); // multiplication with tuple

static const Matrix id4Matrix(4, {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1});
