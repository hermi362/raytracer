#include <cassert>
#include <utility>
#include "matrix.h"
#include "util.h"
#include <memory>



Matrix::Matrix(int dim) {
  N = dim;
  mPtr = std::make_unique<float[]>(N*N);
  for (int i=0 ; i<N*N ; ++i) {mPtr[i] = 0;}
}

Matrix::Matrix(int dim, std::initializer_list<float> values) {
  N = dim;
  mPtr = std::make_unique<float[]>(N*N);

  assert(values.size() >= N*N);
  auto iter = values.begin();
  for (int i=0 ; i<N*N ; ++i) {
    mPtr[i] = *iter;
    ++iter;
  }
}

// copy constructor
Matrix::Matrix(const Matrix& m) {
  N = m.dimension();
  mPtr = std::make_unique<float[]>(N*N);
  for (int i=0 ; i<N*N ; ++i) {
    mPtr[i] = m.mPtr[i];
  }
}

// copy assignment
Matrix& Matrix::operator=(const Matrix& rhs) {
  if (this != &rhs) {  // beware of self-assignment, mat = mat
    N = rhs.N;
    mPtr = std::make_unique<float[]>(N*N);  // this destroys old content of unique_ptr
    for (int i=0 ; i<N*N ; ++i) {
      mPtr[i] = rhs.mPtr[i];
    }
  }
  return *this;
}

// move constructor
Matrix::Matrix(Matrix&& m) noexcept {
  // NOTE: std::exchange(obj, val) assigns val to obj
  // and returns the original value of obj. A useful function
  // for move constructor & move assignment, where the source object
  // should be hollowed out.

  // printf("move constructor\n");
  N = std::exchange(m.N, 0);
  mPtr = std::move(m.mPtr);
}

// move assignment
Matrix& Matrix::operator=(Matrix&& m) noexcept {
  if (this != &m) {   // ignore assigning to yourself
    // printf("move assignment\n");

    // move data over to 'this'
    N = std::exchange(m.N, 0);
    mPtr = std::move(m.mPtr);
  }
  return *this;
}

// return value of matrix at given row, col (0-based)
float Matrix::at(int row, int col) const {
  // do not range-check (trade risk for maximum speed)
  return mPtr[N*row + col];
}

bool Matrix::operator==(const Matrix& rhs) const {
  // if matrix sizes don't match return immediately
  if (dimension() != rhs.dimension())
    return false;
  
  // check every value pair. exit at first mismatch.
  for (int i=0 ; i<N*N ; ++i) {
    if (!isEqualEnough(at(i), rhs.at(i)))
      return false;
  }

  return true;
}

void Matrix::setValue(int row, int col, float value) {
  if (row >= N  ||  col >= N  ||  row < 0  ||  col < 0)   // bounds check
    return;
  // printf("Writing: [%d, %d] <-- %f\n", row, col, value);
  mPtr[N*row + col] = value;
}

std::string Matrix::toString() const {
  const int NB = 20;
  char buffer[NB];
  std::string out = "";

  std::snprintf(buffer, NB, "(%dx%d)\n", N, N);
  out += buffer;
  for (int row=0 ; row<N ; ++row) {
    for (int col=0 ; col<N ; ++col) {
      std::snprintf(buffer, NB, "%.4f  ", mPtr[N*row + col]);
      out += buffer;
    }
    std::snprintf(buffer, NB, "\n");
    out += buffer;
  }

  return out;
}

// Multiplication of two matrices. 
// Note that the return is by-value, not by-reference (Matrix &)
// According to the documentation, the C++ compiler will attempt to use 
// move semantics (i.e. the move assignment operator) to 'move' the
// return value when used in an expression. So even though it might look as though the return
// value is being copied out, that is not necessarily the case.
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


Point operator*(const Matrix& m, const Point& p) {
  assert(m.dimension() == 4);   // this function only works on 4x4 matrices
  Point ret;
  
  ret.x = m.at(0)*p.x + m.at(1)*p.y + m.at(2)*p.z + m.at(3);
  ret.y = m.at(4)*p.x + m.at(5)*p.y + m.at(6)*p.z + m.at(7);
  ret.z = m.at(8)*p.x + m.at(9)*p.y + m.at(10)*p.z + m.at(11);
  ret.w = 1.0f;  // careful, this optimization relies on points always having w=1
  return ret;
}

Vector operator*(const Matrix& m, const Vector& v) {
  assert(m.dimension() == 4);   // this function only works on 4x4 matrices
  Vector ret;

  ret.x = m.at(0)*v.x + m.at(1)*v.y + m.at(2)*v.z; // + m.at(3)*v.w;
  ret.y = m.at(4)*v.x + m.at(5)*v.y + m.at(6)*v.z; // + m.at(7)*v.w;
  ret.z = m.at(8)*v.x + m.at(9)*v.y + m.at(10)*v.z; // + m.at(11)*v.w;
  ret.w = 0.0f; // careful, this optimization relies on vectors always having w=0
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
  if (N == 1) return at(0);
  if (N == 2) {
    // |a b|  -->  (ad - bd)
    // |c d|
    return at(0)*at(3) - at(1)*at(2);
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
  assert(isInvertible());
  
  Matrix ret(N); // create a new matrix of the same size
  float det = determinant();

  for (int row=0 ; row<N ; ++row) {
    for (int col=0 ; col<N ; ++col) {
      float cof = cofactor(row, col);

      // note: col and row are swapped, effectively transposing the output matrix.
      ret.setValue(col, row, cof/det);
    }
  }

  return ret;
}

Matrix getTranslation(float x, float y, float z) {
  Matrix m = id4Matrix;
  m.setValue(0, 3, x);
  m.setValue(1, 3, y);
  m.setValue(2, 3, z);
  return m;
}

Matrix getScaling(float x, float y, float z) {
  Matrix m = id4Matrix;
  m.setValue(0, 0, x);
  m.setValue(1, 1, y);
  m.setValue(2, 2, z);
  return m;
}

Matrix getRotationX(float r) {
  Matrix ret = id4Matrix;
  ret.setValue(1, 1, std::cos(r));
  ret.setValue(1, 2, -std::sin(r));
  ret.setValue(2, 1, std::sin(r));
  ret.setValue(2, 2, std::cos(r));
  return ret;  
}

Matrix getRotationY(float r) {
  Matrix ret = id4Matrix;
  ret.setValue(0, 0, std::cos(r));
  ret.setValue(0, 2, std::sin(r));
  ret.setValue(2, 0, -std::sin(r));
  ret.setValue(2, 2, std::cos(r));
  return ret;  
}

Matrix getRotationZ(float r) {
  Matrix ret = id4Matrix;
  ret.setValue(0, 0, std::cos(r));
  ret.setValue(0, 1, -std::sin(r));
  ret.setValue(1, 0, std::sin(r));
  ret.setValue(1, 1, std::cos(r));
  return ret;  
}

Matrix getShear(float xy, float xz, float yx, float yz, float zx, float zy) {
  Matrix ret = id4Matrix;
  ret.setValue(0, 1, xy);
  ret.setValue(0, 2, xz);
  ret.setValue(1, 0, yx);
  ret.setValue(1, 2, yz);
  ret.setValue(2, 0, zx);
  ret.setValue(2, 1, zy);
  return ret;
}
