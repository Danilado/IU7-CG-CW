#pragma once

#include "Color.hpp"
#include <limits>
#include <vector>

class MyPixmap {
public:
  MyPixmap(size_t width, size_t height, bool createbrightness = false) {
    depth.resize(height, std::vector<double>(
                             width, std::numeric_limits<double>::infinity()));
    if (createbrightness)
      brightness.resize(height, std::vector<double>(width, 0.));
  }
  MyPixmap(size_t width, size_t height, size_t ox, size_t oy,
           bool createbrightness = false)
      : MyPixmap(width, height, createbrightness) {
    offset = {ox, oy};
  }

  const std::pair<size_t, size_t> &getOffset() const { return offset; }
  const std::vector<std::vector<double>> &getDepth() const { return depth; }
  const std::vector<std::vector<double>> &getBrightness() const {
    return brightness;
  }

  const Color &getColor() const { return color; }
  void setColor(const Color &c) { color = c; }

  std::vector<std::vector<double>> &getDepthE() { return depth; }
  std::vector<std::vector<double>> &getBrightnessE() { return brightness; }

private:
  std::pair<size_t, size_t> offset;
  std::vector<std::vector<double>> depth;
  std::vector<std::vector<double>> brightness;
  Color color;
};