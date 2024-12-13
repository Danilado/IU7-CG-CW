#pragma once

#include "Direction.hpp"
#include <unordered_set>

class Rule {
private:
  Direction to;
  int id;
  double probability;

public:
  Rule(const Direction &dir, int id, double probability)
      : to(dir), id(id), probability(probability) {}

  const Direction &getDirection() const { return to; }
  int getId() const { return id; }
  double getProbability() const { return probability; }

  bool operator==(const Rule &other) const {
    return id == other.id && to == other.to;
  }
};

namespace std {
template <> struct hash<Rule> {
  std::size_t operator()(const Rule &r) const {
    return std::hash<int>()(r.getId()) ^
           (std::hash<int>()(r.getDirection()) << 1);
  }
};
} // namespace std