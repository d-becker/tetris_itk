#ifndef RGB_H
#define RGB_H

#include <graphics.hpp>

struct RGB
{
  RGB(int p_r, int p_g, int p_b) : r(p_r), g(p_g), b(p_b) {}
  virtual ~RGB() {}
  RGB(const RGB& other) = default;

  RGB& operator=(const RGB& other) {
    r = other.r;
    g = other.g;
    b = other.b;
    return *this;
  }

  int r;
  int g;
  int b;
};

#endif // RGB_H
