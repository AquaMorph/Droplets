#include "main.h"

using namespace daisy;

int main(void) {
  patch.Init();
  sample_rate = patch.AudioSampleRate();
  droplet_left = GetDroplet(DropletState::kFull);
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
  if (left_menu.InMenu()) {
    left_menu.UpdateMenuPosition();
    if (patch.encoder.RisingEdge()) {
      left_menu.SetInMenu(false);
      if(left_menu.GetState() == MenuState::kSplit) {
	state->ToggleSplit();
	if (state->GetSplitMode()) {
	  droplet_left->UpdateState(DropletState::kLeft);
	  droplet_right = GetDroplet(DropletState::kRight);
	} else {
	  droplet_left->UpdateState(DropletState::kFull);
	  delete droplet_right;
	}
      } else {
	delete droplet_left;
	if(state->GetSplitMode()) {
	  droplet_left = GetDroplet(DropletState::kLeft);
	} else {
	  droplet_left = GetDroplet(DropletState::kFull);
	}
      }
    }
  } else {
    if (patch.encoder.Pressed()) {
      if (patch.encoder.TimeHeldMs() > 500 &&
	  patch.encoder.TimeHeldMs() < 505) {
	left_menu.SetInMenu(true);
      }
    }
  }
}

void ProcessOutputs() {
  if(!left_menu.InMenu()) {
    droplet_left->Control();
    if (state->GetSplitMode()) {
      droplet_right->Control();
    }
  }
}

void ProcessOled() {
  patch.display.Fill(false);
  if (left_menu.InMenu()) {
    left_menu.ProcessMenuOled();
  } else {
    droplet_left->Draw();
    if (state->GetSplitMode()) {
      droplet_right->Draw();
    }
  }
  patch.display.Update();
}

static void AudioThrough(float **in,
			 float **out,
			 size_t size) {
  droplet_left->Process(in, out, size);
  if (state->GetSplitMode()) {
    droplet_right->Process(in, out, size);
  }
}

Droplet* GetDroplet(DropletState state) {
  switch(left_menu.GetState()) {
  case MenuState::kVCO:
    return new VCODroplet(&patch,
			  state,
			  sample_rate);
  case MenuState::kNoise:
  default:
    return new NoiseDroplet(&patch,
			    state);
  }	
}
