#pragma once

#include <functional>
#include <set>
#include <unordered_map>
#include <vector>

class Cell;
class CellRule;

class QWFC {
public:
  QWFC(size_t width, size_t height, const std::vector<Cell> &cells,
       std::function<void(const std::vector<std::vector<std::set<int>>> &)>
           callback = nullptr);

  bool run();

  std::vector<std::vector<Cell>> getResult();

private:
  bool isFullyCollapsed() const;
  std::pair<int, int> findCellWithLeastEntropy() const;
  void collapseCell(int x, int y);
  void propagateConstraints(int x, int y);

private:
  std::unordered_map<int, Cell> cells;
  std::vector<std::vector<std::set<int>>> matrix;
  size_t width, height;
  std::function<void(const std::vector<std::vector<std::set<int>>> &)> callback;
};
