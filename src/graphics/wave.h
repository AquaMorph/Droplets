#pragma once

#ifndef CASCADE_GRAPHICS_WAVE_H_
#define CASCADE_GRAPHICS_WAVE_H_

#include "sprite.h"

enum class WaveShape {kSine, kTriangle, kSaw, kSquare, kRamp};

class Wave: public Sprite {
 private:
  WaveShape wave;
  const double pi = std::acos(-1);
  void DrawShape();
 public:
  Wave(WaveShape, int, int);
};

#endif
