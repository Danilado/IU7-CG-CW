#pragma once

#include "Cell.hpp"

class QWFCHelper {
public:
  static std::vector<Cell> GetCells(double roadprob, double houseprob,
                                    double treeprob, double emptyprob) {
    Cell cross(0, roadprob * .1);
    {
      cross.addConstraint(0, Direction::up, 1.);
      cross.addConstraint(2, Direction::up, 1.);
      cross.addConstraint(3, Direction::up, 1.);
      cross.addConstraint(5, Direction::up, 1.);

      cross.addConstraint(0, Direction::down, 1.);
      cross.addConstraint(2, Direction::down, 1.);
      cross.addConstraint(4, Direction::down, 1.);
      cross.addConstraint(6, Direction::down, 1.);

      cross.addConstraint(0, Direction::right, 1.);
      cross.addConstraint(1, Direction::right, 1.);
      cross.addConstraint(5, Direction::right, 1.);
      cross.addConstraint(6, Direction::right, 1.);

      cross.addConstraint(0, Direction::left, 1.);
      cross.addConstraint(1, Direction::left, 1.);
      cross.addConstraint(3, Direction::left, 1.);
      cross.addConstraint(4, Direction::left, 1.);
    }

    Cell hor(1, roadprob * .25);
    {
      hor.addConstraint(0, Direction::left, 1.);
      hor.addConstraint(1, Direction::left, 1.);
      hor.addConstraint(3, Direction::left, 1.);
      hor.addConstraint(4, Direction::left, 1.);

      hor.addConstraint(0, Direction::right, 1.);
      hor.addConstraint(1, Direction::right, 1.);
      hor.addConstraint(5, Direction::right, 1.);
      hor.addConstraint(6, Direction::right, 1.);

      hor.addConstraint(1, Direction::up, 1.);
      hor.addConstraint(4, Direction::up, 1.);
      hor.addConstraint(6, Direction::up, 1.);
      hor.addConstraint(7, Direction::up, 1.);
      hor.addConstraint(8, Direction::up, 1.);
      hor.addConstraint(9, Direction::up, 1.);

      hor.addConstraint(1, Direction::down, 1.);
      hor.addConstraint(3, Direction::down, 1.);
      hor.addConstraint(5, Direction::down, 1.);
      hor.addConstraint(7, Direction::down, 1.);
      hor.addConstraint(8, Direction::down, 1.);
      hor.addConstraint(9, Direction::down, 1.);
    }

    Cell ver(2, roadprob * .25);
    {
      ver.addConstraint(0, Direction::up, 1.);
      ver.addConstraint(2, Direction::up, 1.);
      ver.addConstraint(3, Direction::up, 1.);
      ver.addConstraint(5, Direction::up, 1.);

      ver.addConstraint(0, Direction::down, 1.);
      ver.addConstraint(2, Direction::down, 1.);
      ver.addConstraint(4, Direction::down, 1.);
      ver.addConstraint(6, Direction::down, 1.);

      ver.addConstraint(2, Direction::left, 1.);
      ver.addConstraint(5, Direction::left, 1.);
      ver.addConstraint(6, Direction::left, 1.);
      ver.addConstraint(7, Direction::left, 1.);
      ver.addConstraint(8, Direction::left, 1.);
      ver.addConstraint(9, Direction::left, 1.);

      ver.addConstraint(2, Direction::right, 1.);
      ver.addConstraint(3, Direction::right, 1.);
      ver.addConstraint(4, Direction::right, 1.);
      ver.addConstraint(7, Direction::right, 1.);
      ver.addConstraint(8, Direction::right, 1.);
      ver.addConstraint(9, Direction::right, 1.);
    }

    Cell br(3, roadprob * .1);
    {
      br.addConstraint(1, Direction::up, 1.);
      br.addConstraint(4, Direction::up, 1.);
      br.addConstraint(6, Direction::up, 1.);
      br.addConstraint(7, Direction::up, 1.);
      br.addConstraint(8, Direction::up, 1.);
      br.addConstraint(9, Direction::up, 1.);

      br.addConstraint(2, Direction::left, 1.);
      br.addConstraint(5, Direction::left, 1.);
      br.addConstraint(6, Direction::left, 1.);
      br.addConstraint(7, Direction::left, 1.);
      br.addConstraint(8, Direction::left, 1.);
      br.addConstraint(9, Direction::left, 1.);

      br.addConstraint(0, Direction::right, 1.);
      br.addConstraint(1, Direction::right, 1.);
      br.addConstraint(5, Direction::right, 1.);
      br.addConstraint(6, Direction::right, 1.);

      br.addConstraint(0, Direction::down, 1.);
      br.addConstraint(2, Direction::down, 1.);
      br.addConstraint(4, Direction::down, 1.);
      br.addConstraint(6, Direction::down, 1.);
    }

    Cell tr(4, roadprob * .1);
    {
      tr.addConstraint(0, Direction::up, 1.);
      tr.addConstraint(2, Direction::up, 1.);
      tr.addConstraint(3, Direction::up, 1.);
      tr.addConstraint(5, Direction::up, 1.);

      tr.addConstraint(1, Direction::down, 1.);
      tr.addConstraint(3, Direction::down, 1.);
      tr.addConstraint(5, Direction::down, 1.);
      tr.addConstraint(7, Direction::down, 1.);
      tr.addConstraint(8, Direction::down, 1.);
      tr.addConstraint(9, Direction::down, 1.);

      tr.addConstraint(2, Direction::left, 1.);
      tr.addConstraint(5, Direction::left, 1.);
      tr.addConstraint(6, Direction::left, 1.);
      tr.addConstraint(7, Direction::left, 1.);
      tr.addConstraint(8, Direction::left, 1.);
      tr.addConstraint(9, Direction::left, 1.);

      tr.addConstraint(0, Direction::right, 1.);
      tr.addConstraint(1, Direction::right, 1.);
      tr.addConstraint(5, Direction::right, 1.);
      tr.addConstraint(6, Direction::right, 1.);
    }

    Cell lb(5, roadprob * .1);
    {
      lb.addConstraint(1, Direction::up, 1.);
      lb.addConstraint(4, Direction::up, 1.);
      lb.addConstraint(6, Direction::up, 1.);
      lb.addConstraint(7, Direction::up, 1.);
      lb.addConstraint(8, Direction::up, 1.);
      lb.addConstraint(9, Direction::up, 1.);

      lb.addConstraint(0, Direction::left, 1.);
      lb.addConstraint(1, Direction::left, 1.);
      lb.addConstraint(3, Direction::left, 1.);
      lb.addConstraint(4, Direction::left, 1.);

      lb.addConstraint(2, Direction::right, 1.);
      lb.addConstraint(3, Direction::right, 1.);
      lb.addConstraint(4, Direction::right, 1.);
      lb.addConstraint(7, Direction::right, 1.);
      lb.addConstraint(8, Direction::right, 1.);
      lb.addConstraint(9, Direction::right, 1.);

      lb.addConstraint(0, Direction::down, 1.);
      lb.addConstraint(2, Direction::down, 1.);
      lb.addConstraint(4, Direction::down, 1.);
      lb.addConstraint(6, Direction::down, 1.);
    }

    Cell tl(6, roadprob * .1);
    {
      tl.addConstraint(0, Direction::up, 1.);
      tl.addConstraint(2, Direction::up, 1.);
      tl.addConstraint(3, Direction::up, 1.);
      tl.addConstraint(5, Direction::up, 1.);

      tl.addConstraint(1, Direction::down, 1.);
      tl.addConstraint(3, Direction::down, 1.);
      tl.addConstraint(5, Direction::down, 1.);
      tl.addConstraint(7, Direction::down, 1.);
      tl.addConstraint(8, Direction::down, 1.);
      tl.addConstraint(9, Direction::down, 1.);

      tl.addConstraint(0, Direction::left, 1.);
      tl.addConstraint(1, Direction::left, 1.);
      tl.addConstraint(3, Direction::left, 1.);
      tl.addConstraint(4, Direction::left, 1.);

      tl.addConstraint(2, Direction::right, 1.);
      tl.addConstraint(3, Direction::right, 1.);
      tl.addConstraint(4, Direction::right, 1.);
      tl.addConstraint(7, Direction::right, 1.);
      tl.addConstraint(8, Direction::right, 1.);
      tl.addConstraint(9, Direction::right, 1.);
    }

    Cell empty(7, emptyprob * 1.);
    {
      empty.addConstraint(1, Direction::up, 1.);
      empty.addConstraint(4, Direction::up, 1.);
      empty.addConstraint(6, Direction::up, 1.);
      empty.addConstraint(7, Direction::up, 1.);
      // empty.addConstraint(8, Direction::up, 1.);
      empty.addConstraint(9, Direction::up, 1.);

      empty.addConstraint(1, Direction::down, 1.);
      empty.addConstraint(3, Direction::down, 1.);
      empty.addConstraint(5, Direction::down, 1.);
      empty.addConstraint(7, Direction::down, 1.);
      // empty.addConstraint(8, Direction::down, 1.);
      empty.addConstraint(9, Direction::down, 1.);

      empty.addConstraint(2, Direction::left, 1.);
      empty.addConstraint(5, Direction::left, 1.);
      empty.addConstraint(6, Direction::left, 1.);
      empty.addConstraint(7, Direction::left, 1.);
      // empty.addConstraint(8, Direction::left, 1.);
      empty.addConstraint(9, Direction::left, 1.);

      empty.addConstraint(2, Direction::right, 1.);
      empty.addConstraint(3, Direction::right, 1.);
      empty.addConstraint(4, Direction::right, 1.);
      empty.addConstraint(7, Direction::right, 1.);
      // empty.addConstraint(8, Direction::right, 1.);
      empty.addConstraint(9, Direction::right, 1.);
    }

    Cell house(8, houseprob * 2.);
    {
      house.addConstraint(1, Direction::up, 1.);
      house.addConstraint(4, Direction::up, 1.);
      house.addConstraint(6, Direction::up, 1.);
      house.addConstraint(7, Direction::up, 1.);
      house.addConstraint(9, Direction::up, 1.);

      house.addConstraint(1, Direction::down, 1.);
      house.addConstraint(3, Direction::down, 1.);
      house.addConstraint(5, Direction::down, 1.);
      house.addConstraint(7, Direction::down, 1.);
      house.addConstraint(9, Direction::down, 1.);

      house.addConstraint(2, Direction::left, 1.);
      house.addConstraint(5, Direction::left, 1.);
      house.addConstraint(6, Direction::left, 1.);
      house.addConstraint(7, Direction::left, 1.);
      house.addConstraint(8, Direction::left, 1.);
      house.addConstraint(9, Direction::left, 1.);

      house.addConstraint(2, Direction::right, 1.);
      house.addConstraint(3, Direction::right, 1.);
      house.addConstraint(4, Direction::right, 1.);
      house.addConstraint(7, Direction::right, 1.);
      house.addConstraint(9, Direction::right, 1.);
    }

    Cell tree(9, treeprob * .7);
    {
      tree.addConstraint(1, Direction::up, 1.);
      tree.addConstraint(4, Direction::up, 1.);
      tree.addConstraint(6, Direction::up, 1.);
      tree.addConstraint(7, Direction::up, 1.);
      tree.addConstraint(9, Direction::up, 1.);

      tree.addConstraint(1, Direction::down, 1.);
      tree.addConstraint(3, Direction::down, 1.);
      tree.addConstraint(5, Direction::down, 1.);
      tree.addConstraint(7, Direction::down, 1.);
      tree.addConstraint(9, Direction::down, 1.);

      tree.addConstraint(2, Direction::left, 1.);
      tree.addConstraint(5, Direction::left, 1.);
      tree.addConstraint(6, Direction::left, 1.);
      tree.addConstraint(7, Direction::left, 1.);
      tree.addConstraint(9, Direction::left, 1.);

      tree.addConstraint(2, Direction::right, 1.);
      tree.addConstraint(3, Direction::right, 1.);
      tree.addConstraint(4, Direction::right, 1.);
      tree.addConstraint(7, Direction::right, 1.);
      tree.addConstraint(9, Direction::right, 1.);
    }

    return {cross, hor, ver, br, tr, lb, tl, empty, house, tree};
  }
};