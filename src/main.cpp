#include "daisysp.h"
#include "daisy_patch.h"

#include <string>

#include "main.h"
#include "util.h"
#include "menu.h"

using namespace daisy;
using namespace daisysp;

DaisyPatch patch;
Menu menu(&patch);

int main(void) {
  patch.Init();
  patch.StartAdc();
  while(true) {
    ProcessControls();
    ProcessOled();
    ProcessOutputs();
  }
}

void ProcessControls() {
  patch.UpdateAnalogControls();
  patch.DebounceControls();
  if (menu.InMenu()) {
    menu.UpdateMenuPosition();
    if (patch.encoder.RisingEdge()) {
      menu.SetInMenu(false);
    }
  } else {
    if (patch.encoder.Pressed()) {
      if (patch.encoder.TimeHeldMs() > 500 && patch.encoder.TimeHeldMs() < 505) {
	menu.SetInMenu(true);
      }
    }
  }
}

void ProcessOutputs() {}

void ProcessOled() {
  patch.display.Fill(false);
  if (menu.InMenu()) {
    menu.ProcessMenuOled();
  } else {
    WriteString(patch, 0, 0, Font_6x8, menu.SelectedName());
  }
  patch.display.Update();
}
