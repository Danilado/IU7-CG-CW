#pragma once

#include "FaceModel.hpp"

class Cube : public FaceModel {
public:
  Cube(double side);

private:
  void createFaces();

  double side;
};