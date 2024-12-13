#ifndef TRANSFORMATION_MATRIX_HPP
#define TRANSFORMATION_MATRIX_HPP

#include "Point2D.hpp"
#include "Point3D.hpp"
#include <array>
#include <cmath>
#include <memory>

class NlohmannJsonAdapter;

class TransformationMatrix {
  friend NlohmannJsonAdapter;

private:
  static const constexpr size_t dim = 3;
  using mat_t = std::array<std::array<double, dim + 1>, dim + 1>;
  mat_t transform;

  double get_2d_x(const Point2D &pt) const noexcept;
  double get_2d_y(const Point2D &pt) const noexcept;
  double get_2d_x(double x, double y) const noexcept;
  double get_2d_y(double x, double y) const noexcept;

  double get_3d_x(const Point3D &pt) const noexcept;
  double get_3d_y(const Point3D &pt) const noexcept;
  double get_3d_z(const Point3D &pt) const noexcept;
  double get_3d_x(double x, double y, double z) const noexcept;
  double get_3d_y(double x, double y, double z) const noexcept;
  double get_3d_z(double x, double y, double z) const noexcept;

  double get_mul_cell(const TransformationMatrix &other, size_t i,
                      size_t j) const noexcept;

  TransformationMatrix get_rotated_around_x(double angle);
  TransformationMatrix get_rotated_around_y(double angle);
  TransformationMatrix get_rotated_around_z(double angle);

  std::array<double, 4> multiply(std::array<double, 4> &point) const;

public:
  TransformationMatrix();
  TransformationMatrix(const TransformationMatrix &other);
  TransformationMatrix(TransformationMatrix &&tmp);
  ~TransformationMatrix() = default;

  void set(size_t i, size_t j, double val) { transform[i][j] = val; };

  Point2D apply(const Point2D &pt) const noexcept;
  void apply_in_place(Point2D &pt) const noexcept;

  Point3D apply(const Point3D &pt) const noexcept;
  void apply_in_place(Point3D &pt) const noexcept;

  void translate(const double dx, const double dy, const double dz) noexcept;
  void translate(const Point3D &pt) noexcept;

  void scale(const double kx, const double ky, const double kz) noexcept;
  void scale(const Point3D &pt) noexcept;

  void rotate(const double ax, const double ay, const double az);
  void rotate(const Point3D &pt);

  void rotate_deg(const double ax, const double ay, const double az);
  void rotate_deg(const Point3D &pt);

  void reset(void);
  void replace(TransformationMatrix &&other) { transform = other.transform; }

  TransformationMatrix operator*(const TransformationMatrix &other) const;
  TransformationMatrix &operator*=(const TransformationMatrix &other);

  Point3D operator*(const Point3D &pt) const;

  TransformationMatrix operator+(const TransformationMatrix &other) const;
  TransformationMatrix &operator+=(const TransformationMatrix &other);

  TransformationMatrix operator-(const TransformationMatrix &other) const;
  TransformationMatrix &operator-=(const TransformationMatrix &other);

  TransformationMatrix operator-() const;

  TransformationMatrix getOffset() const;
  TransformationMatrix getNegOffset() const;

  TransformationMatrix &operator=(TransformationMatrix &&o) {
    transform = std::move(o.transform);

    return *this;
  }

  static TransformationMatrix lookAt(const Point3D &eye, const Point3D &target,
                                     const Point3D &up);

  static TransformationMatrix ortho(double left, double right, double bottom,
                                    double top, double zNear, double zFar);
};

class TranslationMatrix : public TransformationMatrix {
public:
  TranslationMatrix(const double dx, const double dy, const double dz);
};

class ScalingMatrix : public TransformationMatrix {
public:
  ScalingMatrix(const double kx, const double ky, const double kz);
};

class RotationMatrix : public TransformationMatrix {
public:
  RotationMatrix(const double ax, const double ay, const double az,
                 bool deg = false);
};

#endif
