#include "daisysp.h"
#include "daisy_patch.h"

#include <algorithm>
#include <string>

#include "main.h"

using namespace daisy;
using namespace daisysp;

DaisyPatch patch;

const int MENU_SIZE = 8;
const int MAX_CHAR_LENGTH = 15;
std::string menuItems[MENU_SIZE];
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

void SetupMenu() {
  menuItems[0] = "VCO";
  menuItems[1] = "VCA";
  menuItems[2] = "Envelope";
  menuItems[3] = "LFO";
  menuItems[4] = "Logic";
  menuItems[5] = "Noise";
  menuItems[6] = "Delay";
  menuItems[7] = "Reverb";
}

int main(void) {
  patch.Init();
  patch.StartAdc();
  SetupMenu();
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
    return menuItems[position];
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
    patch.display.WriteString(cstr, Font_11x18, !highlighted);
  } else {
    patch.display.WriteString(cstr, Font_7x10, !highlighted);
  }
  //DrawSolidRect(text.size()*7, (position-1)*10, text.size()*7+21, position*10, false);
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
