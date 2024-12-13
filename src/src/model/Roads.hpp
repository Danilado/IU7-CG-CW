#pragma once

#include "Color.hpp"
#include "FaceModel.hpp"

class CrossRoad : public FaceModel {
public:
  CrossRoad(double side, Color color);

private:
  void createFaces(Color color);

  double side;
};

class HorizontalRoad : public FaceModel {
public:
  HorizontalRoad(double side, Color color);

private:
  void createFaces(Color color);

  double side;
};

class VerticalRoad : public FaceModel {
public:
  VerticalRoad(double side, Color color);

private:
  void createFaces(Color color);

  double side;
};

class BRRoad : public FaceModel {
public:
  BRRoad(double side, Color color);

private:
  void createFaces(Color color);

  double side;
};

class TRRoad : public FaceModel {
public:
  TRRoad(double side, Color color);

private:
  void createFaces(Color color);

  double side;
};

class LBRoad : public FaceModel {
public:
  LBRoad(double side, Color color);

private:
  void createFaces(Color color);

  double side;
};

class TLRoad : public FaceModel {
public:
  TLRoad(double side, Color color);

private:
  void createFaces(Color color);

  double side;
};
