#pragma once

#include "Rule.hpp"
#include "Symmetry.hpp"

#include <unordered_set>

class Cell {
  friend class HorizontalSymmetry;
  friend class VerticalSymmetry;
  friend class AllWaySymmetry;

private:
  int id;
  double probability;
  std::vector<SymmetryPtr> sym;
  std::unordered_set<Rule> rules;

public:
  Cell &operator=(const Cell &c) {
    id = c.id;
    sym = c.sym;
    rules = c.rules;

    return *this;
  }

  Cell &operator=(Cell &&c) {
    id = c.id;
    sym = std::move(c.sym);
    rules = std::move(c.rules);

    return *this;
  }

public:
  Cell() = default;
  Cell(int id, double probability = 0) : id(id), probability(probability) {}
  Cell(const Cell &c) {
    id = c.id;
    sym = c.sym;
    rules = c.rules;
    probability = c.probability;
  }
  Cell(const Cell &&c) {
    id = c.id;
    sym = std::move(c.sym);
    rules = std::move(c.rules);
    probability = c.probability;
  }

  void addSymmetry(const SymmetryPtr &symmetry) { sym.push_back(symmetry); }
  void addConstraint(int id, Direction dir, double priority);

  double getProbability() const { return probability; }
  int getId() const { return id; }
  const std::unordered_set<Rule> &getRules() { return rules; }
  std::vector<int> getCompatibleNeighbors(Direction dir) const;
};
