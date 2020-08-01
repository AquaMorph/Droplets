#include "daisysp.h"
#include "daisy_patch.h"

#include <algorithm>
#include <string>

#include "main.h"
#include "menu.h"
#include "util.h"

using namespace daisy;
using namespace daisysp;

DaisyPatch patch;
Util util(&patch);
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
    util.WriteString(0, 0, menu.SelectedName());
  }
  patch.display.Update();
}
