#include "noise_droplet.h"

NoiseDroplet::NoiseDroplet(DaisyPatch* m_patch,
			   float sample_rate,
			   DropletState m_state) {
  patch = m_patch;
  noise.Init();
  filter.Init();
  UpdateState(m_state);
}

void NoiseDroplet::Control() {}

void NoiseDroplet::Process(float** in, float** out, size_t size) {
  for (size_t i = 0; i < size; i += 2) {
    float sig = noise.Process();
    for (size_t chn = chn_min; chn < chn_max; chn++) {
      out[chn][i] = sig;
    }
  }
}

void NoiseDroplet::Draw() {
  for (int h = 0; h < kTitleHeight; h++) {
    for (int w = screen_min; w < screen_max; w++) {
      patch->display.DrawPixel(w, h, rand() % 15 == 0);
    }
  }
  DrawName(patch, "Noise");
}
