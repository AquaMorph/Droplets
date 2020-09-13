#include "noise_droplet.h"

NoiseDroplet::NoiseDroplet(DaisyPatch* m_patch, float sample_rate) {
  noise.Init();
  patch = m_patch;
}

void NoiseDroplet::Control() {}
void NoiseDroplet::Process(float** in, float** out, size_t size) {
  for (size_t i = 0; i < size; i += 2) {
    float sig = noise.Process();
    for (size_t chn = 0; chn < 4; chn++) {
      out[chn][i] = sig;
    }
  }
}
void NoiseDroplet::Draw() {
  WriteString(*patch, 0, 30, Font_6x8, "Test");
}
