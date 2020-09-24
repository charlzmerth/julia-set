#pragma once

#include <array>
#include <utility>
#include <iostream>
#include <iomanip>
#include <sstream>


#define COL_WIDTH 4

template <typename T, int W, int H>
class Matrix {
private:
  T values[W][H] {0};

public:
  Matrix() {

  }

  int width() const {
    return W;
  }

  int height() const {
    return H;
  }

  T get(int x, int y) const {
    return values[x][y];
  }

  void set(int x, int y, T value) {
    values[x][y] = value;
  }

  T& operator[] (const std::pair<int, int>& point) {
    return values[point.first][point.second];
  }

  void printMatrix() {
    for (int y = 0; y < H; y++) {
      for (int x = 0; x < W; x++) {
        double val = this->get(x, y);
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << val;
        std::string valString = stream.str();
        int digits = valString.length();
        std::string padding (COL_WIDTH - digits, ' ');
        std::cout << padding << valString;
      }
      std::cout << std::endl;
    }
  }
};
