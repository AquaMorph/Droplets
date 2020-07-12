#include "daisysp.h"
#include "daisy_patch.h"

#include <string>

#include "main.h"

using namespace daisy;
using namespace daisysp;

DaisyPatch patch;

int main(void) {
  patch.Init();
  patch.StartAdc();
  while(true) {
    ProcessControls();
    ProcessOled();
    ProcessOutputs();
  }
}

void ProcessControls() {}

void ProcessOutputs() {}

void ProcessOled() {
  patch.display.Fill(false);

  std::string str;
  char* cstr = &str[0];
  patch.display.SetCursor(0,0);
  str = "Daisy Template";
  patch.display.WriteString(cstr, Font_7x10, true);

  patch.display.Update();
}
