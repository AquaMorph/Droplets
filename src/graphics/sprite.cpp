#include "sprite.h"

Sprite::Sprite(int m_width, int m_height) {
  width = m_width;
  height = m_height;
  sprite = new bool*[width];
  for (int w = 0; w < width; w++) {
    sprite[w] = new bool[height];
    for (int h = 0; h < height; h++) {
      sprite[w][h] = false;
    }  
  }
}

Sprite::~Sprite() {
  for (int w = 0; w < width; w++) {
    delete[] sprite[w];
  }
  delete[] sprite;
}

void Sprite::AddPixel(int x, int y, bool on) {
  sprite[x][height-y-1] = on;
}

void Sprite::AddLine(int x1,
	     int y1,
	     int x2,
	     int y2,
	     bool on) {
  uint8_t deltaX = abs(x2 - x1);
  uint8_t deltaY = abs(y2 - y1);
  int8_t  signX = ((x1 < x2) ? 1 : -1);
  int8_t  signY = ((y1 < y2) ? 1 : -1);
  int16_t error = deltaX - deltaY;
  int16_t error2;
  
  AddPixel(x2, y2, on);
  while((x1 != x2) || (y1 != y2)) {
    AddPixel(x1, y1, on);
    error2 = error * 2;
    if(error2 > -deltaY) {
      error -= deltaY;
      x1 += signX;
    }
    if(error2 < deltaX) {
      error += deltaX;
      y1 += signY;
    }
  }
}

int Sprite::GetHeight() {
  return height;
}

int Sprite::GetWidth() {
  return width;

}

void Sprite::Draw(DaisyPatch* patch, int x, int y) {
  for (int w = 0; w < width; w++) {
    for (int h = 0; h < height; h++) {
      patch->display.DrawPixel(x+w, y+h,
			      sprite[GetShiftArrayX(w)]
			      [GetShiftArrayY(height-h)]);
    }
  }
}

void Sprite::DrawTile(DaisyPatch* patch,
		      int x1,
		      int y1,
		      int x2,
		      int y2) {
  int x_min = std::min(x1, x2);
  int x_max = std::max(x1, x2);
  int y_min = std::min(y1, y2);
  int y_max = std::max(y1, y2);
  int x, y;
  for (int w = x_min; w < x_max; w++) {
    for (int h = y_min; h < y_max; h++) {
      x = GetShiftArrayX((w-x_min) % width);
      y = GetShiftArrayY((h-y_min) % height);
      patch->display.DrawPixel(w, h, sprite[x][y]);
    }
  }
}

bool** Sprite::GetSprite() {
  return sprite;
}

void Sprite::SetBlank() {
  for (int w = 0; w < width; w++) {
    for (int h = 0; h < height; h++) {
      sprite[w][h] = false;
    }  
  }
}

void Sprite::SetXShift(int x) {
  x_shift = x;
}

void Sprite::SetYShift(int y) {
  y_shift = y;
}

void Sprite::AdjustXShift(int x) {
  x_shift -= x;
}

void Sprite::AdjustYShift(int y) {
  y_shift += y;
}

int Sprite::GetShiftArrayX(int pos) {
  return GetShiftArray(pos, x_shift, width);
}

int Sprite::GetShiftArrayY(int pos) {
  return GetShiftArray(pos, y_shift, height);
}
