#include "util.h"

void DrawSolidRect(DaisyPatch patch,
		   uint8_t x1,
		   uint8_t y1,
		   uint8_t x2,
		   uint8_t y2,
		   bool on) {
  for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
    patch.display.DrawLine(x1, i, x2, i, on);
  }
}

void WriteString(DaisyPatch patch,
		 int x,
		 int y,
		 FontDef font,
		 std::string text,
		 bool on) {
  patch.display.SetCursor(x, y);
  patch.display.WriteString(&text[0], font, on);
}

void WriteString(DaisyPatch patch,
		 int x,
		 int y,
		 FontDef font,
		 std::string text) {
  WriteString(patch, x, y, font, text, true);
}
