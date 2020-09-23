#pragma once

#include <array>
#include <utility>

template <typename T, int W, int H>
class Matrix {
private:
  int values[W][H] {0};

public:
  Matrix() {

  }

  int width() {
    return W;
  }

  int height() {
    return H;
  }

  int& operator[] (const std::pair<int, int>& point) {
    return values[point.first][point.second];
  }
};
