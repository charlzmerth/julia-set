#include <complex>
#include <cmath>
#include <utility>
#include <iostream>
#include "juliaset.hpp"
#include "matrix.hpp"

JuliaSet::JuliaSet() {
  c = std::complex<double>(0.285, 0.01);
  R = 2;
  R2 = R * R;
}

// JuliaSet::JuliaSet(std::complex<double> c) : c {c}, R {std::abs(c)}, R2 {R*R} {
//
// }
//
// JuliaSet::JuliaSet(double real, double imag) : c {std::complex<double>(real, imag)}, R {std::abs(c)}, R2 {R*R} {
//
// }

void JuliaSet::set_c(double real, double imag) {
  c = std::complex<double>(real, imag);
}

inline double JuliaSet::scaleX(double x) {
  return 2 * R * x / width - R;
}

inline double JuliaSet::scaleY(double y) {
  return 2 * R * y / height - R;
}

double JuliaSet::pixelValue(int x, int y) {
  double real = scaleX(x);
  double imag = scaleY(y);
  std::complex<double> z {real, imag};

  int i = 0;
  while (std::norm(z) < R2 && i++ < maxIter) {
    z = z * z + c;
  }

  return static_cast<double>(i) / static_cast<double>(maxIter);
}

Matrix<double, JuliaSet::width, JuliaSet::height> JuliaSet::generate() {
  std::cout << "generating julia set" << std::endl;
  Matrix<double, width, height> result;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      std::pair<int, int> point {x, y};
      result[point] = pixelValue(x, y);
    }
  }
  return result;
}
