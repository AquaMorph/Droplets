#include "wave.h"

Wave::Wave(WaveShape m_wave,
	   int width,
	   int height) : Sprite(width, height) {
  wave = m_wave;
  DrawShape();
}

void Wave::DrawShape() {
  SetBlank();
  int mid = GetWidth()/2;
  int x_max = GetWidth()-1;
  int y_max = GetHeight()-1;
  switch(wave) {
  case WaveShape::kSaw:
    AddLine(0, 0, x_max, y_max, true);
    AddLine(x_max, y_max, x_max, 0, true);
    return;
  case WaveShape::kSquare:
    AddLine(0, 0, mid, 0, true);
    AddLine(mid, 0, mid, y_max, true);
    AddLine(mid, y_max, x_max, y_max, true);
    AddLine(GetWidth()-1, GetHeight()-1, GetWidth()-1, 0, true);
    return;
  case WaveShape::kTriangle:
    AddLine(0, 0, mid, y_max, true);
    AddLine(mid, y_max, x_max, 0, true);
    return;
  case WaveShape::kSine:
  default:
    for (int i = 0; i < GetWidth(); i++) {
      int pixel = (int) round(std::sin(2*pi*((double)(i%x_max)/x_max)) * (y_max/2) + y_max/2);
      AddPixel(i, pixel, true);
    }
    return;
  }
}

void Wave::SetWaveShape(WaveShape m_wave) {
  wave = m_wave;
  DrawShape();
}
