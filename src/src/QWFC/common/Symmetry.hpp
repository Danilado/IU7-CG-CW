#pragma once

#include "Direction.hpp"
#include "Rule.hpp"

#include <memory>
#include <vector>

class Cell;

class Symmetry {
public:
  virtual std::vector<Rule> apply(const Rule &r) const = 0;
  virtual std::vector<Cell> apply(const Cell &c) const = 0;
};

class VerticalSymmetry : public Symmetry {
public:
  virtual std::vector<Rule> apply(const Rule &r) const override;
  virtual std::vector<Cell> apply(const Cell &c) const override;
};

class HorizontalSymmetry : public Symmetry {
public:
  virtual std::vector<Rule> apply(const Rule &r) const override;
  virtual std::vector<Cell> apply(const Cell &c) const override;
};

class AllWaySymmetry : public Symmetry {
public:
  virtual std::vector<Rule> apply(const Rule &r) const override;
  virtual std::vector<Cell> apply(const Cell &c) const override;
};

class NoSymmetry : public Symmetry {
public:
  virtual std::vector<Rule> apply(const Rule &r) const override;
  virtual std::vector<Cell> apply(const Cell &c) const override;
};

using SymmetryPtr = std::shared_ptr<Symmetry>;