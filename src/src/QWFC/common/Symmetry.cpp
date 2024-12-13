#include "Symmetry.hpp"
#include "Cell.hpp"

#include <stdexcept>

std::vector<Rule> VerticalSymmetry::apply(const Rule &r) const {
  std::vector<Rule> res;

  if (r.getDirection() == Direction::right ||
      r.getDirection() == Direction::left)
    return {r};

  for (const auto &dir : {Direction::up, Direction::down})
    res.push_back(Rule(dir, r.getId(), r.getProbability()));

  return res;
};

std::vector<Cell> VerticalSymmetry::apply(const Cell &c) const {
  throw std::runtime_error("Not implemented");
};

std::vector<Rule> HorizontalSymmetry::apply(const Rule &r) const {
  std::vector<Rule> res;

  if (r.getDirection() == Direction::up || r.getDirection() == Direction::down)
    return {r};

  for (const auto &dir : {Direction::right, Direction::left})
    res.push_back(Rule(dir, r.getId(), r.getProbability()));

  return res;
};

std::vector<Cell> HorizontalSymmetry::apply(const Cell &c) const {
  throw std::runtime_error("Not implemented");
};

std::vector<Rule> AllWaySymmetry::apply(const Rule &r) const {
  std::vector<Rule> res;
  res.reserve(Direction::_count);

  for (const auto &dir :
       {Direction::up, Direction::right, Direction::down, Direction::left})
    res.push_back(Rule(dir, r.getId(), r.getProbability()));

  return res;
};

std::vector<Cell> AllWaySymmetry::apply(const Cell &c) const {
  throw std::runtime_error("Not implemented");
};

std::vector<Rule> NoSymmetry::apply(const Rule &r) const { return {r}; };
std::vector<Cell> NoSymmetry::apply(const Cell &c) const { return {c}; };
