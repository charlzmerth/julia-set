#pragma once

#include <complex>
#include "matrix.hpp"

class JuliaSet {
private:
  const int maxIter {1000};
  const std::complex<int> c;
  const double R;
  const double R2;
  static const int width {1280};
  static const int height {720};
  inline int scale(int x);

public:
  JuliaSet(std::complex<double> c);
  int pixelValue(int x, int y);
  Matrix<int, width, height> generate();
};
