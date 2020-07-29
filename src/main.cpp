#include "daisysp.h"
#include "daisy_patch.h"

#include <algorithm>
#include <string>

#include "main.h"

using namespace daisy;
using namespace daisysp;

DaisyPatch patch;

const std::string MENU_ITEMS[] = {"VCO", 
				  "VCA",
				  "Envelope",
				  "LFO",
				  "Logic",
				  "Noise",
				  "Delay",
				  "Reverb",
				  "Turing",
				  "Quantizer"};
const int MENU_SIZE = sizeof(MENU_ITEMS)/sizeof(*MENU_ITEMS);
const int MAX_CHAR_LENGTH = 15;
const int MENU_X[] = {0,  5,  10,  5,  0};
const int MENU_Y[] = {0, 11, 22, 41, 52};
int selectedMenuItem = 0;

void DrawSolidRect(uint8_t x1,
		   uint8_t y1,
		   uint8_t x2,
		   uint8_t y2,
		   bool on) {
  for (int i = std::min(y1, y2); i <= std::max(y1, y2); i++) {
    patch.display.DrawLine(x1, i, x2, i, on);
  }
}

int main(void) {
  patch.Init();
  patch.StartAdc();
  while(true) {
    ProcessControls();
    ProcessOled();
    ProcessOutputs();
  }
}

void FilterMenuSelection() {
  if (selectedMenuItem >= MENU_SIZE) {
    selectedMenuItem = MENU_SIZE - 1;
  } else if (selectedMenuItem < 0) {
    selectedMenuItem = 0;
  }
}

std::string FilterMenuText(int position) {
  if (position >= MENU_SIZE || position < 0) {
    return "";
  } else {
    return MENU_ITEMS[position];
  }
}
void ProcessControls() {
  patch.UpdateAnalogControls();
  patch.DebounceControls();
  selectedMenuItem -= patch.encoder.Increment();
  FilterMenuSelection();
}

void ProcessOutputs() {}

void CreateMenuItem(std::string text, int position, bool highlighted) {
  char* cstr = &text[0];
  text.insert(text.end(), MAX_CHAR_LENGTH-text.size(), ' ');
  patch.display.SetCursor(MENU_X[position-1], MENU_Y[position-1]);
  if (highlighted) {
    DrawSolidRect(0, MENU_Y[2], SSD1309_WIDTH, MENU_Y[2]+17, true);
    patch.display.WriteString(cstr, Font_11x18, !highlighted);
  } else {
    patch.display.WriteString(cstr, Font_7x10, !highlighted);
  }
}

void ProcessOled() {
  patch.display.Fill(false);

  CreateMenuItem(FilterMenuText(selectedMenuItem-2), 1, false);
  CreateMenuItem(FilterMenuText(selectedMenuItem-1), 2, false);
  CreateMenuItem(FilterMenuText(selectedMenuItem), 3, true);
  CreateMenuItem(FilterMenuText(selectedMenuItem+1), 4, false);
  CreateMenuItem(FilterMenuText(selectedMenuItem+2), 5, false);
  
  patch.display.Update();
}
