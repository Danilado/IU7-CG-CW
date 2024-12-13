#include "Cell.hpp"
#include "QWFC.hpp"
#include "QWFCHelper.hpp"
#include "Symmetry.hpp"
#include <iostream>
#include <map>
#include <vector>

#include <cstdlib>
#include <ctime>

int main(void) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  // { Г
  // [ L
  // } ^|
  // ] _|
  std::map<int, std::string> symbolic = {
      {0, "\u253c"}, {1, "\u2500"}, {2, "\u2502"}, {3, "\u250c"},
      {4, "\u2514"}, {5, "\u2510"}, {6, "\u2518"}, {7, " "},
      {8, "\u2302"}, {9, "\u25B5"}};

  std::vector<Cell> cells = QWFCHelper::GetCells(1, 1, 1, 1);

  QWFC qwf(100, 50, cells,
           [](const std::vector<std::vector<std::set<int>>> &matrix) {
             return;
             for (size_t y = 0; y < matrix.size(); ++y) {
               for (size_t x = 0; x < matrix.front().size(); ++x) {
                 for (const auto &val : matrix[y][x])
                   std::cout << val;
                 std::cout << "\t";
               }
               std::cout << std::endl;
             }
             std::cout << std::endl;
           });

  qwf.run();

  auto res = qwf.getResult();
  for (size_t y = 0; y < res.size(); ++y) {
    for (size_t x = 0; x < res.front().size(); ++x)
      std::cout << symbolic.at(res[y][x].getId());
    std::cout << std::endl;
  }

  return 0;
}