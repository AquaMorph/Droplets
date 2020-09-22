#pragma once

#ifndef CASCADE_GRAPHICS_SPRITE_H_
#define CASCADE_GRAPHICS_SPRITE_H_

#include "daisy_patch.h"

using namespace daisy;

class Sprite {
 private:
  int width, height;
  bool** sprite;
 public:
  Sprite(int, int);
  void SetPixel(int, int, bool);
  int GetHeight();
  int GetWidth();
  bool** GetSprite();
  void Draw(DaisyPatch, int, int);
  void DrawTile(DaisyPatch, int, int, int, int);
  void SetBlank();
};

#endif // CASCADE_GRAPHICS_SPRITE_H_
