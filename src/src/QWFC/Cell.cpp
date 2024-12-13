#include "Cell.hpp"
#include <ranges>

void Cell::addConstraint(int id, Direction dir, double priority) {
  Rule r(dir, id, priority);

  if (sym.empty())
    rules.insert(r);
  else
    for (const auto &symmetry : sym) {
      auto rs = symmetry->apply(r);
      rules.insert(rs.begin(), rs.end());
    }
}

std::vector<int> Cell::getCompatibleNeighbors(Direction dir) const {
  std::vector<int> res;

  for (const auto &rule : rules | std::views::filter([&dir](const Rule &r) {
                            return dir == r.getDirection();
                          })) {
    res.push_back(rule.getId());
  }

  return res;
}
