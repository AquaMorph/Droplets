#include "noise_droplet.h"

NoiseDroplet::NoiseDroplet(DaisyPatch* m_patch,
			   float sample_rate,
			   DropletState m_state) {
  noise.Init();
  filter.Init();
  patch = m_patch;
  state = m_state;
}

void NoiseDroplet::Control() {}

void NoiseDroplet::Process(float** in, float** out, size_t size) {
  for (size_t i = 0; i < size; i += 2) {
    float sig = noise.Process();
    size_t chn_min = 0;
    size_t chn_max = 4;
    if (state == DropletState::kLeft) {
      chn_max = 2;
    } else if (state == DropletState::kRight) {
      chn_min = 2;
    }
    for (size_t chn = chn_min; chn < chn_max; chn++) {
      out[chn][i] = sig;
    }
  }
}

void NoiseDroplet::Draw() {
  DrawName(patch);
}


void NoiseDroplet::DrawName(DaisyPatch* patch) {
  int min = 0;
  int max = SSD1309_WIDTH;
  if (state == DropletState::kLeft) {
    max = SSD1309_WIDTH / 2;
  } else if (state == DropletState::kRight) {
    min = SSD1309_WIDTH / 2;
  }
  WriteCenteredString(*patch, (min + max) / 2, 0, Font_6x8, "Noise");
}
