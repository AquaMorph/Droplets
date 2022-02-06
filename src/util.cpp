#include "util.h"

void DrawSolidRect(DaisyPatch* patch,
		   uint8_t x1,
		   uint8_t y1,
		   uint8_t x2,
		   uint8_t y2,
		   bool on) {
  for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
    patch->display.DrawLine(x1, i, x2, i, on);
  }
}

void WriteString(DaisyPatch* patch,
		 int x,
		 int y,
		 FontDef font,
		 std::string text,
		 bool on) {
  patch->display.SetCursor(x, y);
  patch->display.WriteString(&text[0], font, on);
}

void WriteString(DaisyPatch* patch,
		 int x,
		 int y,
		 FontDef font,
		 std::string text) {
  WriteString(patch, x, y, font, text, true);
}

void WriteString(DaisyPatch* patch,
		 int x,
		 int y,
		 std::string text) {
  WriteString(patch, x, y, text, true);
}

void WriteString(DaisyPatch* patch,
		 int x,
		 int y,
		 std::string text,
		 bool on) {
  WriteString(patch, x, y, Font_6x8, text, on);
}

void WriteCenteredString(DaisyPatch* patch,
			 int x,
			 int y,
			 FontDef font,
			 std::string text,
			 bool on) {

  int text_width = font.FontWidth * text.size();
  WriteString(patch, x - (text_width / 2), y, font, text, on);
}

void WriteCenteredString(DaisyPatch* patch,
		 int x,
		 int y,
		 FontDef font,
		 std::string text) {
  WriteCenteredString(patch, x, y, font, text, true);
}

void WriteDoubleCentered(DaisyPatch* patch,
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

void WriteDoubleCentered(DaisyPatch* patch,
			 int x,
			 int y,
			 int width,
			 FontDef font,
			 std::string text) {
  WriteDoubleCentered(patch, x, y, width, font, text, true);
}

std::string WaveToString(uint8_t wf) {
  switch(wf){
  case Oscillator::WAVE_TRI:
    return "Triangle";
  case Oscillator::WAVE_SQUARE:
    return "Square";
  case Oscillator::WAVE_SIN:
    return "Sine";
  case Oscillator::WAVE_SAW:
    return "Saw";
  case Oscillator::WAVE_RAMP:
    return "Ramp";
  case Oscillator::WAVE_POLYBLEP_TRI:
    return "PolyBLEP Triangle";
  case Oscillator::WAVE_POLYBLEP_SQUARE:
    return "PolyBLEP Square";
  case Oscillator::WAVE_POLYBLEP_SAW:
    return "PolyBLEP Saw";
  }
  return "";
}

std::string FloatToString(float num, int places) {
  std::string sign = "";
  int integral = static_cast<int>(num);
  int fractional = static_cast<int>((abs(num) - abs(integral))
				    * pow(10, places));
  if (num < 0.0f && num > -1.0f) {
    sign = "-";
  }
  return sign + std::to_string(integral) + "." + std::to_string(fractional);
}

void DrawTwoDividedRectangles(DaisyPatch* patch,
				int divider,
				int width_min,
				int width_max,
				int rect_one_min,
				int rect_one_max,
				int rect_two_min,
				int rect_two_max) {
  DrawSolidRect(patch,
		width_min,
		rect_one_max,
		width_min+divider,
		rect_one_min,
		true);
  DrawSolidRect(patch,
		width_max-divider,
		rect_two_max,
		width_max,
		rect_two_min,
		true);
}

void DrawFourDividedRectangles(DaisyPatch* patch,
			       int divider,
			       int width_min,
			       int width_max,
			       int rect_one_min,
			       int rect_one_max,
			       int rect_two_min,
			       int rect_two_max,
			       int rect_three_min,
			       int rect_three_max,
			       int rect_four_min,
			       int rect_four_max) {
  DrawTwoDividedRectangles(patch,
			   divider,
			   width_min,
			   width_max,
			   rect_one_min,
			   rect_one_max,
			   rect_four_min,
			   rect_four_max);
  DrawTwoDividedRectangles(patch,
			   divider,
			   width_min+divider,
			   width_max-divider,
			   rect_two_min,
			   rect_two_max,
			   rect_three_min,
			   rect_three_max);
}

int GetShiftArray(int pos,
		  int shift,
		  int array_size) {
  return (array_size + ((pos + shift) % array_size)) % array_size;
}
