#pragma once

#include <complex>
#include "params.hpp"
#include "matrix.hpp"

class JuliaSet {
private:
  std::complex<double> c;
  int maxIter {300};
  double R;
  double R2;
  inline double scaleX(double x);
  inline double scaleY(double y);

public:
  static const int width {CANVAS_WIDTH};
  static const int height {CANVAS_HEIGHT};

  JuliaSet();
  // JuliaSet(std::complex<double> c);
  // JuliaSet(double x, double y);
  void set_c(double real, double imag);
  double pixelValue(int x, int y);
  Matrix<double, width, height> generate();
};
