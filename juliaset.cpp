#include <complex>
#include <cmath>
#include <utility>
#include "juliaset.hpp"
#include "matrix.hpp"

JuliaSet::JuliaSet(int width, int height, double real, double imag, double r, int maxIter) : width {width}, height {height} {
  this->c = std::complex<double>(real, imag);
  this->r = r;
  this->r2 = r * r;
  this->maxIter = maxIter;
}

void JuliaSet::setC(double real, double imag) {
  c = std::complex<double>(real, imag);
}

void JuliaSet::setR(double value) {
  r = value;
  r2 = r * r;
}

void JuliaSet::setCReal(double value) {
  c.real(value);
}

void JuliaSet::setCImag(double value) {
  c.imag(value);
}

inline double JuliaSet::scaleX(double x) {
  return 2 * r * x / width - r;
}

inline double JuliaSet::scaleY(double y) {
  return 2 * r * y / height - r;
}

int JuliaSet::pixelValue(int x, int y) {
  double real = scaleX(x);
  double imag = scaleY(y);
  std::complex<double> z {real, imag};

  int i = 0;
  while (std::norm(z) < r2 && i++ < maxIter) {
    z = z * z + c;
  }

  return i;
}

int JuliaSet::pixelValue(std::pair<int, int> coords) {
  return pixelValue(coords.first, coords.second);
}

void JuliaSet::generate(Matrix<int>& result) {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      std::pair<int, int> point {x, y};
      result[point] = pixelValue(x, y);
    }
  }
}

Matrix<int> JuliaSet::generate() {
  Matrix<int> result(width, height);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      std::pair<int, int> point {x, y};
      result[point] = pixelValue(x, y);
    }
  }
  return result;
}
