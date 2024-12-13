#pragma once

#include "FaceModel.hpp"

class House : public FaceModel {
public:
  House(double side);

private:
  void createFaces();

  double side;
};