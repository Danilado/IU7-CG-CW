#include "QWFC.hpp"

#include "Cell.hpp"
#include "MyMath.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <ranges>
#include <stdexcept>
#include <unordered_set>

namespace {
struct hashFunction {
  size_t operator()(const std::pair<int, int> &x) const {
    return x.first ^ x.second;
  }
};
} // namespace

QWFC::QWFC(size_t width, size_t height, const std::vector<Cell> &cls,
           std::function<void(const std::vector<std::vector<std::set<int>>> &)>
               callback)
    : width(width), height(height), callback(callback) {

  std::vector<int> ids;
  for (const auto &cell : cls) {
    cells.insert({cell.getId(), cell});
    ids.push_back(cell.getId());
  }

  matrix.resize(height);
  for (auto &row : matrix) {
    row.resize(width);
    for (auto &c : row)
      c.insert(ids.begin(), ids.end());
  }
}

bool QWFC::run() {
  while (!isFullyCollapsed()) {
    if (callback) {
      callback(matrix);
    }

    auto [x, y] = findCellWithLeastEntropy();
    collapseCell(x, y);
    propagateConstraints(x, y);
  }
  return true;
}

bool QWFC::isFullyCollapsed() const {
  return std::ranges::all_of(matrix, [](const auto &row) {
    return std::ranges::all_of(
        row, [](const auto &cell) { return cell.size() <= 1; });
  });
}

std::pair<int, int> QWFC::findCellWithLeastEntropy() const {
  int minEntropy = std::numeric_limits<int>::max();
  std::pair<int, int> result = {-1, -1};

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      const auto &cell = matrix[y][x];
      if (cell.size() > 1 && static_cast<int>(cell.size()) < minEntropy) {
        minEntropy = static_cast<int>(cell.size());
        result = {x, y};
      }
    }
  }

  return result;
}

std::vector<std::vector<Cell>> QWFC::getResult() {
  std::vector<std::vector<Cell>> res(height, std::vector<Cell>(width));
  for (size_t y = 0; y < height; ++y)
    for (size_t x = 0; x < width; ++x) {
      int id = *matrix[y][x].begin();
      res[y][x] = cells.at(id);
    }
  return std::move(res);
}

void QWFC::collapseCell(int x, int y) {
  if (x < 0 || y < 0 || x >= width || y >= height)
    return;
  auto &possibleValues = matrix[y][x];
  if (possibleValues.size() == 1)
    return;

  double totalProbability = 0.0;
  for (const auto &value : possibleValues) {
    totalProbability += cells.at(value).getProbability();
  }

  if (totalProbability < MyMath::EPS) {
    throw std::runtime_error("Невозможно продолжить: нет допустимых значений.");
  }

  double random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) *
                  totalProbability;
  double cumulativeProbability = 0.0;
  int chosenValue = *possibleValues.begin();

  for (const auto &value : possibleValues) {
    cumulativeProbability += cells.at(value).getProbability();
    if (random <= cumulativeProbability) {
      chosenValue = value;
      break;
    }
  }

  possibleValues.clear();
  possibleValues.insert(chosenValue);
}

void QWFC::propagateConstraints(int x, int y) {
  std::unordered_set<std::pair<int, int>, hashFunction> visited;
  std::queue<std::pair<int, int>> queue;
  queue.emplace(x, y);

  while (!queue.empty()) {
    auto [cx, cy] = queue.front();
    queue.pop();

    if (visited.contains({cx, cy}))
      continue;

    // std::cout << "propagating for " << cx << " " << cy << " is ";

    const auto &currentValues = matrix[cy][cx];
    // for (const auto &value : currentValues)
    //   std::cout << value;
    // std::cout << std::endl;

    for (const auto &dir :
         {Direction::up, Direction::right, Direction::down, Direction::left}) {
      auto [dx, dy] = to_coords(dir);
      int nx = cx + dx;
      int ny = cy + dy;

      if (visited.contains({nx, ny}))
        continue;

      if (nx < 0 || nx >= width || ny < 0 || ny >= height)
        continue;

      // std::cout << "handling " << nx << " " << ny << std::endl;

      std::set<int> &neighborValues = matrix[ny][nx];
      if (neighborValues.size() == 1)
        continue;

      // std::cout << "current: ";
      // for (const auto &value : neighborValues)
      //   std::cout << value;
      // std::cout << std::endl;

      std::set<int> compatibleValues;
      for (const auto &value : currentValues) {
        auto compats = cells.at(value).getCompatibleNeighbors(dir);
        compatibleValues.insert(compats.begin(), compats.end());
      }

      // std::cout << "compatible: ";
      // for (const auto &value : compatibleValues)
      //   std::cout << value;
      // std::cout << std::endl;

      std::vector<int> res;
      res.resize(cells.size());
      auto end = std::set_intersection(
          neighborValues.begin(), neighborValues.end(),
          compatibleValues.begin(), compatibleValues.end(), res.begin());
      res.resize(std::distance(res.begin(), end));

      if (res.size() == matrix[ny][nx].size())
        continue;

      // std::cout << "result: ";
      // for (const auto &value : res)
      //   std::cout << value;
      // std::cout << std::endl;

      matrix[ny][nx].clear();
      matrix[ny][nx].insert(res.begin(), res.end());

      queue.emplace(nx, ny);
    }
    visited.emplace(cx, cy);
  }
}
