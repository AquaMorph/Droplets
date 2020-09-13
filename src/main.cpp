#include "daisysp.h"
#include "daisy_patch.h"

#include <string>

#include "main.h"
#include "util.h"
#include "menu.h"
#include "droplets/droplet.h"
#include "droplets/noise_droplet.h"

using namespace daisy;
using namespace daisysp;

DaisyPatch patch;
Menu menu(&patch);
Droplet* droplet;

int main(void) {
  patch.Init();
  float samplerate = patch.AudioSampleRate();
  droplet = new NoiseDroplet(&patch, samplerate);
  patch.StartAdc();
  patch.StartAudio(AudioThrough);
  
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
  droplet->Draw();
  patch.display.Update();
}

static void AudioThrough(float **in, float **out, size_t size) {
  patch.UpdateAnalogControls();
  droplet->Process(in, out, size);
}

