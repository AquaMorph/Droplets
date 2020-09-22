#include "droplet.h"

Droplet::Droplet(DaisyPatch* m_patch, DropletState m_state) {
  patch = m_patch;
  UpdateState(m_state);
}

void Droplet::DrawName(DaisyPatch* patch, std::string name) {
  WriteCenteredString(*patch, (screen_min + screen_max) / 2, 0,
		      Font_6x8, name);
}

void Droplet::UpdateState(DropletState m_state) {
  state = m_state;
  screen_min = 0;
  screen_max = SSD1309_WIDTH;
  if (state == DropletState::kLeft) {
    chn_max = 2;
    screen_max = SSD1309_WIDTH / 2;
  } else if (state == DropletState::kRight) {
    chn_min = 2;
    screen_min = SSD1309_WIDTH / 2;
  }
}

void Droplet::AnimationInc() {
  if (count == animation_rate) {
    animation_count++;
    count = 0;
  }
  count++;
  //animation_count = animation_count % animation_rate;
  WriteCenteredString(*patch, (screen_min + screen_max) / 2, 40,
		      Font_6x8, std::to_string(animation_count));
}

void Droplet::SetAnimationRate(int rate) {
  animation_rate = rate;
}
