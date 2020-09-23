#include <complex>
#include <cmath>
#include <utility>
#include "juliaset.hpp"
#include "matrix.hpp"

JuliaSet::JuliaSet(std::complex<double> c) : c {c}, R {std::abs(c)}, R2 {R*R} {

}

// TODO: implement
inline int JuliaSet::scaleX(int x) {
  return ...;
}

inline int JuliaSet::scaleY(int y) {
  return ...;
}

int JuliaSet::pixelValue(int x, int y) {
  int real = scale(x);
  int imag = scale(y);

  std::complex<int> z {real, imag};

  int i = 0;
  while (std::norm(z) < R2 && i++ < maxIter)
    z = z * z + c;

  if (i == maxIter)
    return 0;
  else
    return i;
}

Matrix<int, JuliaSet::width, JuliaSet::height>JuliaSet::generate() {
  Matrix<int, width, height> result;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      std::pair<int, int> point {x, y};
      result[point] = pixelValue(x, y);
    }
  }
  return result;
}
