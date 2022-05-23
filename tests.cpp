#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>

#include "point.h"
#include "vector.h"
#include "color.h"
#include "film.h"
#include "matrix.h"
#include "ray.h"
#include "sphere.h"
#include "util.h"
#include "intersections.h"
#include "light.h"

void runTests() {
  {
    Point p;
    assert(p == Point(0,0,0));
    assert(Point() == Point(0,0,0));
  }
  {
    // equality test
    Point t1(1.0, 1.0, 1.0, 1.0);
    Point t2(1.0, 1.0, 1.0, 1.0);
    assert(t1 == t2);
    t1 = Point(1.0, 1.0, 1.0, 1.0);
    t2 = Point(1.00000001, 0.99999999, 1.0, 1);
    assert(t1 == t2);    
    t1 = Point(1.0, 1.0, 1.0, 1.0);
    t2 = Point(2, 1, 1.0, 1);
    assert(t1 != t2);    
  }
  {
    // adding points and vectors
    Point p1 = Point(1.0, 1.2, 4.2);
    Vector v1 = Vector(10,10,10);
    Point p2 = p1 + v1;
    assert(p2 ==  Point(1.0+10, 1.2+10, 4.2+10, 1.0+0.0));
    p2 = v1 + p1;
    assert(p2 ==  Point(1.0+10, 1.2+10, 4.2+10, 1.0+0.0));

    // adding a point and a vector yields a point (not a vector)
    p2 = Point(1,2,3);
    Vector v2(10,10,10);
    assert(p2 + v2 == Point(11,12,13));
    assert(v2 + p2 == Point(11,12,13));

    // adding two vectors yields a vector (not a point)
    Vector v3(6,7,8);
    Vector v4(10,10,10);
    assert(v3+v4 == Vector(16,17,18));
    assert(v4+v3 == Vector(16,17,18));
  }
  {
    // subtract two points
    auto p1 = Point(3,2,1);
    auto p2 = Point(5,6,7);
    assert(p1 - p2 == Vector(-2, -4, -6));
  }
  {
    // subtract a vector from a point
    auto p = Point(3,2,1);
    auto v = Vector(5,6,7);
    assert(p - v == Point(-2, -4, -6));
  }
  {
    // subtract two vectors
    auto v1 = Vector(3,2,1);
    auto v2 = Vector(5,6,7);
    assert(v1 - v2 == Vector(-2, -4, -6));
  }
  {
    // subtracting a vector from the zero vector
    auto zero = Vector(0,0,0);
    auto v = Vector(1, -2, 3);
    assert(zero - v == Vector(-1, 2, -3));
  }
  {
    // negating a point
    auto a = Point(1, -2, 3, -4);
    assert( -a == Point(-1, 2, -3, 4));
    // negating a vector
    auto v = Vector(1, -2, 3, -4);
    assert( -v == Vector(-1, 2, -3, 4));
  }
  {
    // chained addition
    Vector v1(0,1,2);
    Vector v2(4,5,6);
    Vector v3(8,9,0);
    assert(v1+v2+v3 == Vector(12,15,8));
    // std::cout<<"vector chained addition also OK\n";
  }
  {
    // multiply a vector by a scalar
    Vector a(1, -2, 3, -4);
    assert( a*3.5 == Vector(3.5, -7, 10.5, -14));
    assert( 3.5*a == Vector(3.5, -7, 10.5, -14));
    assert( a*0.5 == Vector(0.5, -1, 1.5, -2));
    assert( 0.5*a == Vector(0.5, -1, 1.5, -2));
  }
  {
    // divide vector by a scalar
    Vector a(1, -2, 3, -4);
    assert( a/2 == Vector(0.5, -1, 1.5, -2));
  }
  {
    // magnitude of vector
    Vector v(1, 0, 0);
    assert(v.magnitude() == 1);
    v = Vector(0, 1, 0);
    assert(v.magnitude() == 1);
    v = Vector(0, 0, 1);
    assert(v.magnitude() == 1);

    v = Vector(1, 2, 3);
    auto epsilon = std::abs(v.magnitude() - std::sqrt(14));
    assert(epsilon < 0.00001);
    v = Vector(-1, -2, -3);
    epsilon = std::abs(v.magnitude() - std::sqrt(14));
    assert(epsilon < 0.00001);
  }
  {
    // normalizing vectors
    Vector v(4, 0, 0);
    assert(v.normalize() == Vector(1, 0, 0));
    v = Vector(1, -2, 3);
    assert(v.normalize() == Vector(1/std::sqrt(14), -2/std::sqrt(14), 3/std::sqrt(14)));
    assert(std::abs(v.normalize().magnitude() - 1) < 0.00001 );
  }
  {
    // dot product
    Vector a(1, 2, 3);
    Vector b(2, 3, 4);
    assert(a.dot(b) == 20);
    assert(b.dot(a) == 20);
  }
  {
    // cross product
    Vector a(1, 2, 3);
    Vector b(2, 3, 4);
    assert(a.cross(b) == Vector(-1, 2, -1));
    assert(b.cross(a) == Vector(1, -2, 1));
  }
  {
    // scalar multiplication
    Vector v(1,2,3);
    assert(1.1 * v == Vector(1.1, 2.2, 3.3));
    assert(v * 1.1 == Vector(1.1, 2.2, 3.3));

  }

  {
    // color tests
    Color c(-0.5, 0.4, 1.7);
    // std::cout << c.toString() << std::endl;
    assert(c == Color(-0.5, 0.4, 1.7));
    
    Color c1(0.9, 0.6, 0.75);
    Color c2(0.7, 0.1, 0.25);
    assert(c1 == Color(0.9, 0.6, 0.75));  // equality
    assert(c1+c2 == Color(1.6, 0.7, 1.0));  // add
    assert(c1-c2 == Color(0.2, 0.5, 0.5));  // subtract
    assert(c1*2 == Color(1.8, 1.2, 1.5));   // mult by scalar
    assert(2*c1 == Color(1.8, 1.2, 1.5));

    Color c3(1, 0.2, 0.4);
    Color c4(0.9, 1, 0.1);
    assert(c3*c4 == Color(0.9, 0.2, 0.04));
  }

  {
    // film tests
    const int W=480*1;
    const int H=270*1;
    Film film(W, H);
    // std::cout << film.toString();
    for (int i=0; i<W*H; ++i) 
      assert(film.pixelAt(i) == Color(0,0,0));

    for (int y=0; y<H; ++y) 
      for (int x=0; x<W; ++x)
        assert(film.pixelAt(x, y) == Color(0,0,0));

    Color red(1, 0, 0);
    film.writePixel(2, 3, red);
    assert(film.pixelAt(2, 3) == red);

    // create a film, add some pixel data, check output.
    Film film2(5, 3);
    Color c1(1.5, 0, 0);
    Color c2(0, 0.5, 0);
    Color c3(-0.5, 0, 1);
    film2.writePixel(0, 0, c1);
    film2.writePixel(2, 1, c2);
    film2.writePixel(4, 2, c3);
    // std::cout << film2.toPPM();
    assert(film2.toPPM() == "P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 127 0 0 0 0 0 0 0 \n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 \n\n");

    // create a film, fill it with pixels of same color, check output.
    Film film3(10, 2);
    for (int y=0 ; y<2 ; ++y) {
      for (int x=0 ; x<10 ; ++x) {
        film3.writePixel(x, y, Color(1, 0.8, 0.6));
      }   
    }
    // std::cout << film3.toPPM();
    assert(film3.toPPM() == "P3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 \n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 \n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 \n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 \n\n");
  }

  {
    // matrix tests

    // test a 4x4 matrix
    Matrix m1(4, {1.0, 2.0,   3.0,  4.0, \
                  5.5, 6.5,   7.5,  8.5, \
                  9,    10,   11,   12,  \
                  13.5, 14.5, 15.5, 16.5});

    assert(isEqualEnough(m1.at(0,0) , 1.0));
    assert(isEqualEnough(m1.at(0,3) , 4.0));
    assert(isEqualEnough(m1.at(1,0) , 5.5));
    assert(isEqualEnough(m1.at(1,2) , 7.5));
    assert(isEqualEnough(m1.at(2,2) , 11));
    assert(isEqualEnough(m1.at(3,0) , 13.5));
    assert(isEqualEnough(m1.at(3,2) , 15.5));

    // test a 2x2 matrix
    Matrix m2(2, {-3, 5,  \
                  1,  -2});
    assert(isEqualEnough(m2.at(0,0), -3));
    assert(isEqualEnough(m2.at(0,1), 5));
    assert(isEqualEnough(m2.at(1,0), 1));
    assert(isEqualEnough(m2.at(1,1), -2));

    // test a 3x3 matrix
    Matrix m3(3, {-3, 5,  0, \
                  1,  -2, -7,\
                  0,  1,  1});
    assert(isEqualEnough(m3.at(0,0), -3));
    assert(isEqualEnough(m3.at(1,1), -2));
    assert(isEqualEnough(m3.at(2,2), 1));


    // test matrix comparison
    Matrix m4(4, {1,  2,  3,  4, \
                  5,  6,  7,  8, \
                  9,  8,  7,  6,  \
                  5,  4,  3,  2});
    Matrix m5(4, {1,  2,  3,  4, \
                  5,  6,  7,  8, \
                  9,  8,  7,  6,  \
                  5,  4,  3,  2});
    assert(m4 == m5);

    Matrix m6(m4);  // test copy constructor
    Matrix m7(2);
    assert(m6 != m7);
    m7 = m5;        // test copy assignment
    assert(m6 == m7);
    m7.setValue(1, 1, 6.0001);
    assert(m6 != m7);

    // std::cout << m7.toString();

    Matrix m8;
    Matrix m9(1);
    assert(m8 == m9);

    // test matrix multiplication
    Matrix m10(4, {1,  2,  3,  4, \
                  5,  6,  7,  8, \
                  9,  8,  7,  6,  \
                  5,  4,  3,  2});
    Matrix m11(4, {-2,  1,  2,  3, \
                  3,  2,  1,  -1, \
                  4,  3,  6,  5,  \
                  1,  2,  7,  8});
    Matrix m12(4, {20,  22,  50,  48, \
                  44,  54,  114,  108, \
                  40,  58,  110,  102,  \
                  16,  26,  46,  42});
    
    // std::cout << (m11 * m10).toString();
    assert(m10*m11 == m12);

    // test matrix-point multiplication
    Matrix m13(4, {1,  2,  3,  4, 
                  2,  4,  4,  2, 
                  8,  6,  4,  1,  
                  0,  0,  0,  1});
    Point t1(1, 2, 3, 1);
    assert((m13 * t1) == Point(18, 24, 33, 1));

    // test matrix-vector multiplication
    Vector v1(1, 2, 3, 0);
    assert((m13 * v1) == Vector(14, 22, 32, 0));


    // test (4x4) identity matrix
    Matrix m14(4, {1,  2,  3,  4, 
                  2,  4,  4,  2, 
                  8,  6,  4,  1,  
                  0,  0,  0,  1});
    assert((m14 * id4Matrix) == m14);

    // test transposing
    Matrix m15(4, {0,9,3,0, 
                   9,8,0,8,
                   1,8,5,3,
                   0,0,5,8});
    Matrix m16(4, {0,9,1,0, 
                   9,8,8,0,
                   3,0,5,5,
                   0,8,3,8});
    // std::cout << m15.transpose().toString();
    assert(m15.transpose() == m16);

    // test identity matrix
    assert(id4Matrix.transpose() == id4Matrix);
    Matrix m17 = id4Matrix;
    Matrix m18 = id4Matrix.transpose();
    Matrix m19 = m18.transpose();
    assert(m17 == m18 && m18 == m19);

    // test 2x2 determinant
    Matrix m20(2, {1,5,  
                  -3,2});
    assert(m20.determinant() == 17);

    // test submatrix
    assert(m20.submatrix(0, 0) == Matrix(1, {2}));
    assert(m20.submatrix(0, 1) == Matrix(1, {-3}));

    Matrix m21(3, {1,2,3, 
                   4,5,6,
                   7,8,9});

    // std::cout << m21.toString();
    // std::cout << m21.submatrix(0,0).toString();
    Matrix m22(2, {5,6, 
                   8,9});
    assert(m21.submatrix(0,0) == m22);
    Matrix m23(2, {1,3, 
                   7,9});
    assert(m21.submatrix(1,1) == m23);
    Matrix m24(2, {1,2, 
                   4,5});
    assert(m21.submatrix(2,2) == m24);
    Matrix m25(2, {1,2, 
                   7,8});
    assert(m21.submatrix(1,2) == m25);
    

    Matrix m26(4, {1 ,2 ,3 ,10, 
                   4 ,5 ,6 ,20,
                   7 ,8 ,9 ,30,
                   11,22,33,40});
    Matrix m27(3, {1 ,2 ,   10, 

                   7 ,8 ,   30,                   
                   11,22,   40});
    assert(m26.submatrix(1,2) == m27);
    Matrix m28(3, {2 ,3, 10, 
                   5 ,6, 20,
                   8 ,9, 30});
    assert(m26.submatrix(3,0) == m28);
    
    Matrix m30(3, {1,2,3,4,5,6,7,8,9}); 
    Matrix m31(std::move(m30));
    m31 = std::move(m30);

    Matrix m32(3, {3,5,0,2,-1,-7,6,-1,5});
    assert(isEqualEnough(m32.minor(1,0), 25));
    assert(isEqualEnough(m32.minor(0,0), -12));
    assert(isEqualEnough(m32.minor(1,1), 15));
    assert(isEqualEnough(m32.minor(2,2), -13));

    assert(isEqualEnough(m32.cofactor(0,0), -12));
    assert(isEqualEnough(m32.cofactor(1,0), -25));

    Matrix m33(3, {1,2,6, -5,8,-4, 2,6,4});
    assert(isEqualEnough(m33.cofactor(0,0), 56));
    assert(isEqualEnough(m33.cofactor(0,1), 12));
    assert(isEqualEnough(m33.cofactor(0,2), -46));
    assert(isEqualEnough(m33.determinant(), -196));

    Matrix m34(4, {-2,-8,3,5, -3,1,7,3, 1,2,-9,6, -6,7,7,-9});
    assert(isEqualEnough(m34.cofactor(0,0), 690));
    assert(isEqualEnough(m34.cofactor(0,1), 447));
    assert(isEqualEnough(m34.cofactor(0,2), 210));
    assert(isEqualEnough(m34.cofactor(0,3), 51));
    assert(isEqualEnough(m34.determinant(), -4071));

    Matrix m35(4, {6,4,4,4, 5,5,7,6, 4,-9,3,-7, 9,1,7,-6});
    assert(isEqualEnough(m35.determinant(), -2120));
    assert(m35.isInvertible());

    Matrix m36(4, {-4,2,-2,-3, 9,6,2,6, 0,-5,1,-5, 0,0,0,0});
    assert(isEqualEnough(m36.determinant(), 0));
    assert(m36.isInvertible() == false);
    

    // test matrix inversion
    Matrix m37(4, {-5,2,6,-8, 1,-5,1,8, 7,7,-6,-7, 1,-3,7,4});
    Matrix m38 = m37.inverse();
    assert(isEqualEnough(m37.determinant(), 532));
    assert(isEqualEnough(m37.cofactor(2,3), -160));
    assert(isEqualEnough(m38.at(3,2), -160.0/532));
    assert(isEqualEnough(m37.cofactor(3,2), 105));
    assert(isEqualEnough(m38.at(2,3), 105.0/532));
    assert(m38 == Matrix(4, {0.21805,  0.45113, 0.24060, -0.04511, 
                            -0.80827, -1.45677, -0.44361, 0.52068,
                            -0.07895, -0.22368, -0.05263, 0.19737,
                            -0.52256, -0.81391, -0.30075, 0.30639})); 

    Matrix m40(4, {8,-5,9,2, 7,5,6,1, -6,0,9,6, -3,0,-9,-4});
    Matrix m41;
    m41 = m40.inverse();
    assert(m41 == Matrix(4, {
              -0.153846153846153846, -0.153846153846153846,  -0.282051282051282051, -0.538461538461538461,
              -0.076923076923076923,  0.1230769230769230768,  0.025641025641025641,  0.0307692307692307692,
               0.358974358974358974,  0.358974358974358974,   0.435897435897435897,  0.923076923076923076,
              -0.692307692307692307, -0.692307692307692307,  -0.76923076923076923,  -1.923076923076923075  }));

    Matrix m42(4, {9,3,0,9, -5,-2,-6,-3, -4,9,6,4, -7,6,6,2});
    assert(m42.inverse() == Matrix(4, {
              -0.0407407407407407374, -0.0777777777777777714, 0.1444444444444444326, -0.222222222222222204, 
              -0.0777777777777777714, 0.0333333333333333306, 0.3666666666666666366, -0.333333333333333306, 
              -0.0290123456790123433, -0.1462962962962962843, -0.1092592592592592503, 0.129629629629629619, 
              0.1777777777777777632, 0.0666666666666666612, -0.2666666666666666448, 0.333333333333333306 }));


    // test the formula   (A * B) * inv(B) == A
    Matrix matA(4, {3,-9,7,3, 3,-8,2,-9, -4,4,4,1, -6,5,-1,1});
    Matrix matB(4, {8,2,2,2, 3,-1,7,0, 7,0,5,4, 6,-2,0,5});
    Matrix matC = matA * matB;
    assert(matC * matB.inverse() == matA);
    assert((matA * matB) * matB.inverse() == matA);
    assert(matA * matB.inverse() * matB * matA.inverse() == id4Matrix);

    // test trans(inv(A)) == inv(trans(A))
    assert(matA.inverse().transpose() == matA.transpose().inverse());
  }

  {
    // translation test
    Matrix t1 = getTranslation(5, -3, 2);
    Point p(-3, 4, 5);
    assert( t1 * p == Point(2, 1, 7) );
  }

  {
    // invert translation matrix to get reverse translation
    Matrix t1 = getTranslation(5, -3, 2);
    Matrix inv = t1.inverse();
    Point p(-3, 4, 5);
    assert( inv * p == Point(-8, 7, 3));
  }

  {
    // multiplying a translation by a vector should not change the vector
    Matrix t1 = getTranslation(5, -3, 2);
    Vector v(-3, 4, 5);
    assert(t1 * v == v);
  }

  {
    // scaling applied to a point
    Matrix t1 = getScaling(2, 3, 4);
    Point p1(-4, 6, 8);
    Point p2 = t1 * p1;
    assert(p2 == Point(-8, 18, 32));
  }

  {
    // scaling applied to a vector
    Matrix t1 = getScaling(2, 3, 4);
    Vector v1(-4, 6, 8);
    Vector v2 = t1 * v1;
    assert(v2 == Vector(-8, 18, 32));
  }

  {
    // multiplying by inverse of a scaling matrix
    Matrix t1 = getScaling(2, 3, 4);
    Matrix inv = t1.inverse();
    Vector v1(-4, 6, 8);
    assert(inv * v1 == Vector(-2, 2, 2));
  }

  {
    // reflection
    Matrix t1 = getScaling(-1, 1, 1);
    Point p1(2, 3, 4);
    assert(t1 * p1 == Point(-2, 3, 4));
  }

  { 
    // rotation around x axis
    const Point p(0, 1, 0);
    Matrix half_quarter = getRotationX(PI/4);
    Matrix full_quarter = getRotationX(PI/2);
    assert(half_quarter * p == Point(0, ROOT2 / 2, ROOT2 / 2));
    assert(full_quarter * p == Point(0, 0, 1));

    // inverse of rotation about x axis
    Matrix inv = half_quarter.inverse();
    assert(inv * p == Point(0, ROOT2 / 2, -ROOT2 / 2));
  }

  {
    // rotation about the y axis
    const Point p(0, 0, 1);
    Matrix half_quarter = getRotationY(PI/4);
    Matrix full_quarter = getRotationY(PI/2);
    assert(half_quarter * p == Point(ROOT2 / 2, 0, ROOT2 / 2));
    assert(full_quarter * p == Point(1, 0, 0));
  }

  {
    // rotation about the z axis
    const Point p(0, 1, 0);
    Matrix half_quarter = getRotationZ(PI/4);
    Matrix full_quarter = getRotationZ(PI/2);
    assert(half_quarter * p == Point(-ROOT2 / 2, ROOT2 / 2, 0));
    assert(full_quarter * p == Point(-1, 0, 0));
  }

  {
    // shear tests

    Matrix shear;
    Point p;

    // a shearing xform that moves x in proportion to y
    shear = getShear(1,0,0,0,0,0);
    p = Point(2,3,4);
    assert(shear * p == Point(5,3,4));


    // a shearing xform that moves x in proportion to z
    shear = getShear(0,1,0,0,0,0);
    p = Point(2,3,4);
    assert(shear * p == Point(6,3,4));

    // a shearing xform that moves y in proportion to x
    shear = getShear(0,0,1,0,0,0);
    p = Point(2,3,4);
    assert(shear * p == Point(2,5,4));

    // a shearing xform that moves y in proportion to z
    shear = getShear(0,0,0,1,0,0);
    p = Point(2,3,4);
    assert(shear * p == Point(2,7,4));

    // a shearing xform that moves z in proportion to x
    shear = getShear(0,0,0,0,1,0);
    p = Point(2,3,4);
    assert(shear * p == Point(2,3,6));

    // a shearing xform that moves z in proportion to y
    shear = getShear(0,0,0,0,0,1);
    p = Point(2,3,4);
    assert(shear * p == Point(2,3,7));
  }

  { 
    // chaining transformations pt1

    // individual transforms are applied in sequence
    Point p(1,0,1);
    Matrix A = getRotationX(PI/2);
    Matrix B = getScaling(5,5,5);
    Matrix C = getTranslation(10,5,7);
    // apply rotation first
    Point p2 = A * p;
    assert(p2 == Point(1, -1, 0));
    // then apply scaling
    Point p3 = B * p2;
    assert(p3 == Point(5, -5, 0));
    // then apply translation
    Point p4 = C * p3;
    assert(p4 == Point(15, 0, 7));
  }
  {
    // chaining transformations pt2

    // chained transformations must be applied in reverse order
    Point p(1,0,1);
    Matrix A = getRotationX(PI/2);
    Matrix B = getScaling(5,5,5);
    Matrix C = getTranslation(10,5,7);
    Matrix T = C * B * A;
    assert(T * p == Point(15,0,7));
  }

  // ray tests
  {
    Point origin(1,2,3);
    Vector direction(4,5,6);
    Ray r(origin, direction);
    assert(r.getOrigin() == origin && r.getDirection() == direction);
  }
  {
    // compute a point from a distance
    Ray r(Point(2,3,4), Vector(1,0,0));
    assert(r.getPosition(0) == Point(2,3,4));
    assert(r.getPosition(1) == Point(3,3,4));
    assert(r.getPosition(-1) == Point(1,3,4));
    assert(r.getPosition(2.5) == Point(4.5,3,4));
  }
  {
    //Test intersection of ray with sphere

    // ray passing through sphere centre
    Ray r(Point(0,0,-5), Vector(0,0,1));
    Sphere s;
    float thit;
    bool hit = intersect(r, &s, thit);
    assert(hit == true);
    assert(isEqualEnough(thit, 4.0));

    // ray touching sphere at a tangent
    r = Ray(Point(0,1,-5), Vector(0,0,1));
    hit = intersect(r, &s, thit);
    assert(hit == true);
    assert(isEqualEnough(thit, 5.0));

    // ray misses sphere
    r = Ray(Point(0,2,-5), Vector(0,0,1));
    hit = intersect(r, &s, thit);
    assert(hit == false);

    // ray originates inside sphere
    r = Ray(Point(0,0,0), Vector(0,0,1));
    hit = intersect(r, &s, thit);
    assert(hit == true);
    assert(isEqualEnough(thit, -1.0));

    // sphere is completely behind the ray
    r = Ray(Point(0,0,5), Vector(0,0,1));
    hit = intersect(r, &s, thit);
    assert(hit == true);
    assert(isEqualEnough(thit, -6.0));
  }


  {
    // ray transformations

    // translating a ray
    Ray r(Point(1,2,3), Vector(0,1,0));
    Matrix m = getTranslation(3,4,5);
    Ray r2 = r.transform(m);
    assert(r2.getOrigin() == Point(4,6,8));
    assert(r2.getDirection() == Vector(0,1,0));

    // scaling a ray
    m = getScaling(2,3,4);
    r2 = r.transform(m);
    assert(r2.getOrigin() == Point(2,6,12));
    assert(r2.getDirection() == Vector(0,3,0));
  }

  {
    // sphere transformations

    // intersecting a scaled sphere with a ray
    Ray r(Point(0,0,-5), Vector(0,0,1));
    Sphere s;
    s.setTransform(getScaling(2,2,2));
    float thit;
    bool hit = intersect(r, &s, thit);
    assert(isEqualEnough(thit, 3));

    // intersecting a translated sphere with a ray
    r = Ray(Point(0,0,-5), Vector(0,0,1));
    s.setTransform(getTranslation(5,0,0));
    hit = intersect(r, &s, thit);
    assert(hit == false);
  }

  {
    // computing normal on a transformed sphere
    Sphere s;
    s.setTransform(getTranslation(0, 1, 0));
    Vector n = s.getNormalAt(Point(0, 1+ROOT2/2, -ROOT2/2));
    assert(n == Vector(0, ROOT2/2, -ROOT2/2));    
  }
  {
    // computing normal on a transformed sphere
    Sphere s;
    s.setTransform(getScaling(1, 0.5, 1) * getRotationZ(PI/5));
    Vector n = s.getNormalAt(Point(0, ROOT2/2, -ROOT2/2));
    assert(n == Vector(0, 0.97014, -0.24254));
  }
  {
    // reflecting a vector approaching at 45 deg
    Vector v(1, -1, 0);
    Vector n(0,  1, 0);
    Vector r = reflect(v, n);
    assert(r == Vector(1, 1, 0));
  }
  {
    // reflecting a vector off a slanted surface
    Vector v(0, -1, 0);
    Vector n(ROOT2/2,  ROOT2/2, 0);
    Vector r = reflect(v, n);
    assert(r == Vector(1, 0, 0));
  }
  {
    // lighting
    Material material;
    material.shininess = 200;
    PointLight light(Point(0,0,-10), Color(1,1,1));
    Point point(0,0,0);

    Vector eyev(0,0,-1);
    Vector normalv(0,0,-1);

    Color result;

    // lighting with the eye between the light and the surface
    eyev = Vector(0,0,-1);
    normalv = Vector(0,0,-1);
    light.position = Point(0,0,-10);
    result = lighting(material, light, point, eyev, normalv);
    assert(result == Color(1.9,1.9,1.9));

    // lighting with eye offset 45 deg
    eyev = Vector(0, ROOT2/2, -ROOT2/2);
    normalv = Vector(0,0,-1);
    light.position = Point(0,0,-10);
    result = lighting(material, light, point, eyev, normalv);
    assert(result == Color(1.0,1.0,1.0));

    // lighting with light offset 45 deg
    eyev = Vector(0,0,-1);
    normalv = Vector(0,0,-1);
    light.position = Point(0,10,-10);
    result = lighting(material, light, point, eyev, normalv);
    float L = 0.1 + 0.9*ROOT2/2;
    assert(result == Color(L, L, L));

    // lighting with eye in the path of reflection vector    
    eyev = Vector(0, -ROOT2/2, -ROOT2/2);
    normalv = Vector(0,0,-1);
    light.position = Point(0,10,-10);
    result = lighting(material, light, point, eyev, normalv);
    L = 1.6363853; //0.1 + 0.9*ROOT2/2 + 0.9;
    assert(result == Color(L, L, L));

    // lighting with the light behind the surface
    eyev = Vector(0,0,-1);
    normalv = Vector(0,0,-1);
    light.position = Point(0,0,10);
    result = lighting(material, light, point, eyev, normalv);
    L = 0.1f;
    assert(result == Color(L, L, L));
  }
    
  std::cout << "Tests completed.\n";
}

// Use the film to draw a projectile's parabolic trajectory
struct Projectile {
  Point position;
  Vector velocity;
};
struct Environment {
  Vector gravity;
  Vector wind;
};
Projectile tick(Environment env, Projectile proj) {
  Projectile p1;
  p1.position = proj.position + proj.velocity;
  p1.velocity = proj.velocity + env.gravity + env.wind;
  return p1;
}

void playProjectileGame() {
  Projectile p;
  p.position = Point(0, 30, 0);
  p.velocity = Vector(8, 10, 0);
  Environment e;
  e.gravity = Vector(0, -1, 0);
  e.wind    = Vector(-0.2, 0, 0);

  Film film(160, 100);
  auto i = 30;
  while(i-- > 0)
  {
    p = tick(e, p);
    printf("(%2.3f,%2.3f)  [%2.3f, %2.3f]\n", p.position.x, p.position.y, p.velocity.x, p.velocity.y);
    const int x = (int)p.position.x;
    const int y = (int)p.position.y;
    if (x > 0 && x < film.width() && y > 0 && y < film.height()) {
      film.writePixel(x, film.height()-y, Color(1,0,0));
    }
  }

  std::ofstream ostrm("projectile.ppm");
  ostrm << film.toPPM();

}



// Use film and rotation matrix to draw the hour pips of a clock face
void drawClock() {
  std::cout << "Drawing clock..." << std::endl;
  Film film(100, 100);
  // draw a point at the center of the clock
  film.writePixel(film.width()/2, film.width()/2, Color(1,1,1));

  Point hourHand(40,0,0);
  Matrix rotOneHour = getRotationZ(PI/6);
  for (int i=0 ; i<12 ; i++) {
    hourHand = rotOneHour * hourHand;
    film.writePixel(film.width()/2 + hourHand.x, film.height()/2 + hourHand.y, Color(1,0,0));
  }

  std::ofstream ostrm("clock.ppm");
  ostrm << film.toPPM();
  std::cout << "Finished." << std::endl;
}


// ray-trace a sphere against a square film using hit/nonhit only.
// This should draw a solid circle on film.
void rayTraceSphere() {
  std::cout << "Rendering sphere..." << std::endl;

  int film_pixels = 100;
  Film film(film_pixels, film_pixels);
  Color red(1,0,0);  // color to draw sphere's silhouette

  Point ray_origin(0,0,-10.f);
  float wall_z = 10.f;
  float wall_size = 7.f;
  float pixel_size = wall_size / film_pixels;
  float half = wall_size / 2;

  PointLight light(Point(-10,0,0), Color(0.8, 0.4, 0.0));

  Sphere sphere;
  // sphere.setTransform(getTranslation(0.5,0,0));
  // sphere.setTransform(getScaling(1, 0.5, 1));
  // sphere.setTransform(getRotationZ(PI/4) * getScaling(1, 0.2, 1) * getTranslation(0.8, 0, 0) );
  // sphere.setTransform(getShear(1,0,0,0,0,0) * getScaling( .5, 1, 1) );
  sphere.setTransform(getRotationX(PI/8) * getScaling(1.5, 0.2, 1) );

  for (int y=0 ; y<film_pixels ; y++) {
    float world_y = half - pixel_size * y;

    for (int x=0 ; x<film_pixels ; x++) {
      float world_x = -half + pixel_size * x;

      // describe the point on wall that ray will target
      Point position(world_x, world_y, wall_z);

      Vector ray_direction = Vector(position - ray_origin).normalize();
      Ray r(ray_origin, ray_direction);
      float thit;
      bool hit;
      hit = intersect(r, &sphere, thit);

      if (hit) {
        Point wrldIntersect = sphere.transform * r.getPosition(thit);
        Vector eyev = (ray_origin - wrldIntersect).normalize();
        Vector normal = sphere.getNormalAt(wrldIntersect);
        Color shade = lighting(sphere.material, light, wrldIntersect, eyev, normal);
        film.writePixel(x, y, shade);
      }

    } // x++

  if (y%10==0) std::cout << "line " << y << std::endl;
  } // y++

  std::ofstream ostrm("sphere.ppm");
  ostrm << film.toPPM();
  std::cout << "Finished." << std::endl;

}