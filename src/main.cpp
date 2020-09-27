#include "main.h"

using namespace daisy;

int main(void) {
  patch.Init();
  sample_rate = patch.AudioSampleRate();
  droplet = GetDroplet();
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
      delete droplet;
      droplet = GetDroplet();
    }
  } else {
    if (patch.encoder.Pressed()) {
      if (patch.encoder.TimeHeldMs() > 500 &&
	  patch.encoder.TimeHeldMs() < 505) {
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
    droplet->Draw();
  }
  patch.display.Update();
}

static void AudioThrough(float **in,
			 float **out,
			 size_t size) {
  droplet->Process(in, out, size);
}

Droplet* GetDroplet() {
  switch(menu.GetState()) {
  case MenuState::kVCO:
    return new VCODroplet(&patch,
			  DropletState::kRight,
			  sample_rate);
  case MenuState::kNoise:
  default:
    return new NoiseDroplet(&patch,
			    DropletState::kFull);
  }	
}
