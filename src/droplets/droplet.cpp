#include "droplet.h"

void Droplet::DrawName(DaisyPatch* patch, std::string name) {
  int min = 0;
  int max = SSD1309_WIDTH;
  if (state == DropletState::kLeft) {
    max = SSD1309_WIDTH / 2;
  } else if (state == DropletState::kRight) {
    min = SSD1309_WIDTH / 2;
  }
  WriteCenteredString(*patch, (min + max) / 2, 0, Font_6x8, name);
}
