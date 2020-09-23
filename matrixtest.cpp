#include <string>
#include <iostream>
#include <utility>
#include <cmath>
#include "matrix.hpp"

#define W 10
#define H 7
#define COL_WIDTH 5

void printMatrix(Matrix<int, W, H>& matrix) {
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      int val = matrix[std::make_pair(x, y)];
      std::string valString = std::to_string(val);
      int digits = valString.length();
      std::string padding (COL_WIDTH - digits, ' ');
      std::cout << padding << valString;
    }
    std::cout << std::endl;
  }
}

int main() {
  Matrix<int, W, H> test;
  test[std::make_pair(2, 0)] = 4;
  test[std::make_pair(2, 0)] = 6;
  test[std::make_pair(0, 0)] = 45;
  test[std::make_pair(8, 1)] = -34;
  test[std::make_pair(1, 1)] = 0;
  test[std::make_pair(2, 0)] = 4111;

  printMatrix(test);
  return 0;
}
