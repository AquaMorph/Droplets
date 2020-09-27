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

void WriteCenteredString(DaisyPatch patch,
			 int x,
			 int y,
			 FontDef font,
			 std::string text,
			 bool on) {

  int text_width = font.FontWidth * text.size();
  WriteString(patch, x - (text_width / 2), y, font, text, on);
}

void WriteCenteredString(DaisyPatch patch,
		 int x,
		 int y,
		 FontDef font,
		 std::string text) {
  WriteCenteredString(patch, x, y, font, text, true);
}

void WriteDoubleCentered(DaisyPatch patch,
			 int x,
			 int y,
			 int width,
			 FontDef font,
			 std::string text,
			 bool on) {
  // If only one line is needed
  if ((int) text.length() * font.FontWidth < width) {
    WriteCenteredString(patch,
			x,
			y - font.FontHeight/2,
			font,
			text,
			on);
  } else {
    unsigned int split = text.find(" ");
    if (split == std::string::npos) {
      split = width / font.FontWidth;
    }
    std::string row1 = text.substr(0, split);
    std::string row2 = text.substr(split+1, text.length());
    WriteCenteredString(patch,
			x,
			y - font.FontHeight,
			font,
			row1,
			on);
    WriteCenteredString(patch,
			x,
			y,
			font,
			row2,
			on);
  }
}

void WriteDoubleCentered(DaisyPatch patch,
			 int x,
			 int y,
			 int width,
			 FontDef font,
			 std::string text) {
  WriteDoubleCentered(patch, x, y, width, font, text, true);
}
