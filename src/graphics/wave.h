#pragma once

#ifndef CASCADE_GRAPHICS_WAVE_H_
#define CASCADE_GRAPHICS_WAVE_H_

#include "sprite.h"

enum class WaveShape {kSine, kTriangle, kSaw, kSquare, kRamp};

class Wave: public Sprite {
 private:
  WaveShape wave;
  const double pi = std::acos(-1);

  /*
   * Changes pixels of the graphic based on the set wave shape.
   */
  void DrawShape();
 public:
  /*
   * Contstructor for wave shape sprite.
   *
   * @param m_wave wave shape
   * @param width sprite width
   * @param height sprite height
   */
  Wave(WaveShape m_wave,
       int width,
       int height);

  /*
   * Sets the sprites wave shape.
   * 
   * @param m_wave wave shape
   */
  void SetWaveShape(WaveShape m_wave);
};

#endif
