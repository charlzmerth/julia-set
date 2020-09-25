#pragma once

#include <utility>
// #include <array>
// #include <iostream>
// #include <iomanip>
// #include <sstream>

#define COL_WIDTH 4

template <typename T>
class Matrix {
private:
  T *values;
  int width;
  int height;

public:
  Matrix(int width, int height) {
    values = new T[width * height] {};
    this->width = width;
    this->height = height;
  }

  ~Matrix() {
    delete[] values;
  }

  int getWidth() const {
    return this->width;
  }

  int getHeight() const {
    return this->height;
  }

  T get(int x, int y) const {
    return values[x + width * y];
  }

  void set(int x, int y, T value) {
    values[x + width * y] = value;
  }

  T& operator[] (const std::pair<int, int>& point) {
    return values[point.first + width * point.second];
  }

  // void printMatrix() {
  //   for (int y = 0; y < height; y++) {
  //     for (int x = 0; x < width; x++) {
  //       int val = this->get(x, y);
  //       // std::stringstream stream;
  //       // stream << std::fixed << std::setprecision(2) << val;
  //       // std::string valString = stream.str();
  //       std::string valString = std::to_string(val);
  //       int digits = valString.length();
  //       std::string padding (COL_WIDTH - digits, ' ');
  //       std::cout << padding << valString;
  //     }
  //     std::cout << std::endl;
  //   }
  // }
};
