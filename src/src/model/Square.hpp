#pragma once

#include "Color.hpp"
#include "FaceModel.hpp"

class Square : public FaceModel {
public:
  Square(double side, Color color);

private:
  void createFaces(Color color);

  double side;
};