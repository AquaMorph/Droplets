#include "droplet.h"

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
