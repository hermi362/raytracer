#include <cassert>
#include <utility>
#include "matrix.h"
#include "util.h"



Matrix::Matrix(int dim) {
  N = dim;
  mData = new float[N*N];
  for (int i=0 ; i<N*N ; ++i) {mData[i] = 0;}
}

Matrix::Matrix(int dim, std::initializer_list<float> values) {
  N = dim;
  mData = new float[N*N];

  assert(values.size() >= N*N);
  auto iter = values.begin();
  for (int i=0 ; i<N*N ; ++i) {
    mData[i] = *iter;
    ++iter;
  }
}

// copy constructor
Matrix::Matrix(const Matrix& m) {
  // printf("copy constructor\n");
  N = m.dimension();
  mData = new float[N*N];
  for (int i=0 ; i<N*N ; ++i) {
    mData[i] = m.mData[i];
  }
}

// copy assignment
Matrix& Matrix::operator=(const Matrix& rhs) {
  if (this != &rhs) {  // beware of self-assignment, mat = mat
    // printf("copy assignment\n");
    delete[] mData;
    N = rhs.N;
    mData = new float[N*N];
    for (int i=0 ; i<N*N ; ++i) {
      mData[i] = rhs.mData[i];
    }
  }
  return *this;
}

// move constructor
Matrix::Matrix(Matrix&& m) noexcept
  : N(std::exchange(m.N, 0))
  , mData(std::exchange(m.mData, nullptr)) 
{
  // NOTE: std::exchange(obj, val) assigns val to obj
  // and returns the original value of obj. A useful function
  // for move constructor & move assignment
  printf("move constructor\n");
}

// move assignment
Matrix& Matrix::operator=(Matrix&& m) noexcept {
  if (this != &m) {   // ignore assigning to yourself
    printf("move assignment\n");

    // free up any existing matrix data
    delete[] mData;

    // move data over to 'this'
    N     = std::exchange(m.N, 0);
    mData = std::exchange(m.mData, nullptr);
  }
  return *this;
}

Matrix::~Matrix() {
  if (mData != nullptr)
    delete[] mData;
}

float Matrix::at(int row, int col) const {
  // do not range-check (trade risk for maximum speed)
  return mData[N*row + col];
}

bool Matrix::operator==(const Matrix& rhs) const {
  // if matrix sizes don't match return immediately
  if (dimension() != rhs.dimension())
    return false;

  static const float ERR = 0.00001;  // permissible error below which two floating-point values are considered equal
  
  // check every value pair. exit at first mismatch.
  for (int i=0 ; i<N*N ; ++i) {
    if (std::abs(at(i) - rhs.at(i)) > ERR)
      return false;
  }

  return true;
}

void Matrix::setValue(int row, int col, float value) {
  if (row >= N  ||  col >= N  ||  row < 0  ||  col < 0)   // bounds check
    return;
  // printf("Writing: [%d, %d] <-- %f\n", row, col, value);
  mData[N*row + col] = value;
}

std::string Matrix::toString() const {
  const int NB = 20;
  char buffer[NB];
  std::string out = "";

  std::snprintf(buffer, NB, "(%dx%d)\n", N, N);
  out += buffer;
  for (int row=0 ; row<N ; ++row) {
    for (int col=0 ; col<N ; ++col) {
      std::snprintf(buffer, NB, "%.4f  ", mData[N*row + col]);
      out += buffer;
    }
    std::snprintf(buffer, NB, "\n");
    out += buffer;
  }

  return out;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  assert(lhs.dimension() == rhs.dimension());
  const int N = lhs.dimension();

  Matrix ret(N);
  for( int row=0 ; row<N ; ++row ) {
    for( int col=0 ; col<N ; ++col ) {
      float sum = 0;
      for( int k=0 ; k<N ; ++k ) {
        sum += lhs.at(row, k) * rhs.at(k, col);
      }
      ret.setValue(row, col, sum);
    }
  }

  return ret;
}

Tuple operator*(const Matrix& lhs, const Tuple& rhs) {
  assert(lhs.dimension() == 4);   // this function only works on 4x4 matrices
  Tuple ret;
  ret.x = lhs.at(0,0)*rhs.x + lhs.at(0,1)*rhs.y + lhs.at(0,2)*rhs.z + lhs.at(0,3)*rhs.w;
  ret.y = lhs.at(1,0)*rhs.x + lhs.at(1,1)*rhs.y + lhs.at(1,2)*rhs.z + lhs.at(1,3)*rhs.w;
  ret.z = lhs.at(2,0)*rhs.x + lhs.at(2,1)*rhs.y + lhs.at(2,2)*rhs.z + lhs.at(2,3)*rhs.w;
  ret.w = lhs.at(3,0)*rhs.x + lhs.at(3,1)*rhs.y + lhs.at(3,2)*rhs.z + lhs.at(3,3)*rhs.w;
  return ret;
}

// return a transposed copy of 'this'
Matrix Matrix::transpose() const {
  Matrix ret(N);

  for (int row=0 ; row<N ; ++row)
    for (int col=0 ; col<N ; ++col)
      ret.setValue(row, col, this->at(col, row));

  return ret;
}

float Matrix::determinant() const {
  if (N == 1) return mData[0];
  if (N == 2) {
    // |a b|  -->  (ad - bd)
    // |c d|
    return mData[0]*mData[3] - mData[1]*mData[2];
  } else {
    // sum (element*cofactor) along top row
    const int row = 0;
    float sum = 0;
    for (int col=0 ; col<N ; ++col) {
      sum += at(row, col) * cofactor(row, col);
    }
    return sum;
  }

}

// return the cofactor: minor at row,col  with appropriately modified sign
float Matrix::cofactor(int row, int col) const {
  int factor = ((row+col) % 2 == 0) ? 1 : -1;
  return factor * minor(row, col);
}

// return the minor (determinant of the submatrix at row,col)
float Matrix::minor(int row, int col) const {
  return submatrix(row, col).determinant();
}

// return submatrix that remains when col and row are removed
Matrix Matrix::submatrix(int RR, int CC) const {
  assert(N > 1);
  assert(RR >=0  && RR <N);
  assert(CC >=0  && CC <N);
  Matrix ret(N-1);  // prepare the return matrix, one size smaller

  std::vector<int> rs, cs;  // size N-1, contains id's of 'this' matrix e.g. {0, 2, 3}
  for (int i=0 ; i<N ; ++i) {
    if (i != RR)   // skip row RR
      rs.push_back(i);
    if (i != CC)   // skip col CC
      cs.push_back(i);
  }
  // postcondition: rs contains the row ids of the submatrix, 
  //                cs contains the col ids of the submatrix.

  // iterate over rs and cs
  // NOTE: the indices (r0, c0) of the return matrix ret, are different from 
  // the indices (r1, c1) of the source matrix, 'this'.
  int r1 = 0, c1 = 0;
  for (int r0 : rs) {
    for (int c0 : cs) {
      // printf("[%d,%d, %.1f]  ", r0,c0,at(r0, c0));
      ret.setValue(r1, c1, at(r0, c0));
      c1++;
    }
    // printf("\n");
    r1++;
    c1 = 0;
  }

  return ret;
}

bool Matrix::isInvertible() const {
  return !isEqualEnough(0, determinant());
}

// return inverse as a new Matrix
Matrix Matrix::inverse() const {

}