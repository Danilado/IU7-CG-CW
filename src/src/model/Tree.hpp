#pragma once

#include "FaceModel.hpp"

class Tree : public FaceModel {
public:
  Tree(double height);

private:
  void createFaces();

  double side;
};