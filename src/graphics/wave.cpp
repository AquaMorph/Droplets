#include "wave.h"

Wave::Wave(WaveShape m_wave, int width, int height) : Sprite(width, height) {
  wave = m_wave;
  DrawShape();
}

void Wave::DrawShape() {
  SetBlank();
  int mid = GetWidth()/2;
  switch(wave) {
  case WaveShape::kTriangle:
    AddLine(0, GetHeight()+1, mid, 0, true);
    AddLine(mid, 0, GetWidth()+1, GetHeight(), true);
    return;
  case WaveShape::kSine:
  default:
    for (int i = 0; i < GetWidth(); i++) {
      int pixel = (int) round(std::sin(2*pi*((double)(i%GetWidth())/GetWidth())) * (GetHeight()/2) + GetHeight()/2);
      AddPixel(i, pixel, true);
    }
    return;
  }
}
