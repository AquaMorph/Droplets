#pragma once

#ifndef CASCADE_GRAPHICS_SPRITE_H_
#define CASCADE_GRAPHICS_SPRITE_H_

#include "daisy_patch.h"

using namespace daisy;

class Sprite {
 private:
  int width, height;
  bool** sprite;
  int x_shift = 0;
  int y_shift = 0;
  int GetShiftArray(int, int, int);
  int GetShiftArrayX(int);
  int GetShiftArrayY(int);
 public:
  Sprite(int, int);
  ~Sprite();
  void AddPixel(int, int, bool);
  void AddLine(int, int, int, int, bool);
  int GetHeight();
  int GetWidth();
  bool** GetSprite();
  void Draw(DaisyPatch, int, int);
  void DrawTile(DaisyPatch, int, int, int, int);
  void SetBlank();
  void SetXShift(int);
  void SetYShift(int);
  void AdjustXShift(int);
  void AdjustYShift(int);
};

#endif // CASCADE_GRAPHICS_SPRITE_H_
