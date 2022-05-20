#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <initializer_list>
#include <memory>

#include "point.h"
#include "vector.h"


// implements a square (NxN) matrix
// elements are in row-major order, unlike OpenGL's column-major order
class Matrix {
  private:
    int N;          // matrix size (N*N)
    std::unique_ptr<float[]> mPtr;  // store matrix data as 1-dimensional array in a managed pointer
  public:
    Matrix(int dim);  // create zero-filled matrix of given dim
    Matrix(int dim, std::initializer_list<float> values); // initialize from list of floats
    Matrix() : Matrix(1) {} // override the default constructor. good practise.

    Matrix(const Matrix& m);              // copy constructor
    Matrix& operator=(const Matrix& rhs); // copy assignment

    Matrix(Matrix&& m) noexcept; // move constructor
    Matrix& operator=(Matrix&& m) noexcept; // move assignment
    
    // default destructor is fine, managed pointer's deleter will deallocate its matrix data
    ~Matrix()=default;

    int dimension() const { return N; } // get matrix size (N)
    float at(int row, int col) const;  // get single matrix value at (row,col), first element is at (0,0)
    float at(int i) const { return mPtr[i]; } // get matrix value at array index i

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
Point  operator*(const Matrix& lhs, const Point& rhs);  // multiplication with point
Vector operator*(const Matrix& lhs, const Vector& rhs); // multiplication with vector

static const Matrix id4Matrix(4, {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1});

// return the 4x4 translation matrix as a new matrix
Matrix getTranslation(float x, float y, float z);

// Return the 4x4 scaling matrix as a new matrix
Matrix getScaling(float x, float y, float z);

// Return the 4x4 rotation matrix about x, y or z axis. Rotation direction is
// clockwise when looking at origin from positive side of x, y or z axis.
Matrix getRotationX(float rads);
Matrix getRotationY(float rads);
Matrix getRotationZ(float rads);

// Return the 4x4 shear matrix
// xy means x moved in proportion to y
// xz means x moved in proportion to z
// etc
Matrix getShear(float xy, float xz, float yx, float yz, float zx, float zy);
