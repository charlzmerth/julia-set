#pragma once

#include <complex>
#include <utility>
#include "matrix.hpp"

class JuliaSet {
private:
  double r;
  double r2;
  inline double scaleX(double x);
  inline double scaleY(double y);

public:
  const int width;
  const int height;
  std::complex<double> c;
  int maxIter;

  JuliaSet(int width, int height, double real = 0.5, double imag = 0.5, double r = 2, int maxIter = 300);
  void setC(double real, double imag);
  void setCReal(double value);
  void setCImag(double value);
  void setR(double value);

  int pixelValue(int x, int y);
  int pixelValue(std::pair<int, int> coords);
  void generate(Matrix<int>& result);
  Matrix<int> generate();
};
