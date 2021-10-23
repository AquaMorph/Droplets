#include "main.h"

using namespace daisy;

int main(void) {
  patch.Init();
  sample_rate = patch.AudioSampleRate();
  droplet_left = GetDroplet(DropletState::kFull);
  selected_menu = left_menu;
  patch.StartAdc();
  patch.StartAudio(AudioThrough);
  
  while(true) {
    ProcessControls();
    ProcessOled();
    ProcessOutputs();
  }
}

void ProcessControls() {
  patch.ProcessAnalogControls();
  patch.encoder.Debounce();
  // Handle menu interactions
  if (selected_menu->InMenu()) {
    selected_menu->UpdateMenuPosition();
    // Handle menu selection
    if (patch.encoder.RisingEdge()) {
      selected_menu->SetInMenu(false);
      // Split selected
      if(selected_menu->GetState() == MenuState::kSplit) {
	manager->ToggleSplit();
	// Enable split
	if (manager->GetSplitMode()) {
	  droplet_left->UpdateState(DropletState::kLeft);
	  droplet_right = GetDroplet(DropletState::kRight);
	}
	// Disable split
	else {
	  droplet_left->UpdateState(DropletState::kFull);
	  delete droplet_right;
	}
      }
      // Switch side
      else if (selected_menu->GetState() == MenuState::kChange) {
	if (selected_menu == left_menu) {
	  selected_menu = right_menu;
	} else {
	  selected_menu = left_menu;
	}
      }
      // Enable new mode
      else {
	if(manager->GetSplitMode()) {
	  if (selected_menu == left_menu) {
	    delete droplet_left;
	    droplet_left = GetDroplet(DropletState::kLeft);
	  } else {
	    delete droplet_right;
	    droplet_right = GetDroplet(DropletState::kRight);
	  }
	} else {
	  delete droplet_left;
	  droplet_left = GetDroplet(DropletState::kFull);
	}
      }
    }
  }
  // Check if entering menu
  else {
    if (patch.encoder.Pressed()) {
      if (patch.encoder.TimeHeldMs() > 500 &&
	  patch.encoder.TimeHeldMs() < 505) {
	selected_menu->SetInMenu(true);
      }
    }
  }
}

void ProcessOutputs() {
  if(!selected_menu->InMenu()) {
    droplet_left->Control();
    if (manager->GetSplitMode()) {
      droplet_right->Control();
    }
  }
}

void ProcessOled() {
  patch.display.Fill(false);
  if (selected_menu->InMenu()) {
    selected_menu->ProcessMenuOled();
  } else {
    droplet_left->Draw();
    if (manager->GetSplitMode()) {
      droplet_right->Draw();
    }
  }
  patch.display.Update();
}

static void AudioThrough(AudioHandle::InputBuffer in,
			 AudioHandle::OutputBuffer out,
			 size_t size) {
  droplet_left->Process(in, out, size);
  if (manager->GetSplitMode()) {
    droplet_right->Process(in, out, size);
  }
}

Droplet* GetDroplet(DropletState state) {
  switch(selected_menu->GetState()) {
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
