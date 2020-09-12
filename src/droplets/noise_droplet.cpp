#include "noise_droplet.h"

NoiseDroplet::NoiseDroplet(float sample_rate) {
  noise.Init();
}

void NoiseDroplet::Control(float ctr_1, float ctr_2, float ctr_3, float ctr_4) {}
void NoiseDroplet::Process(float** in, float** out, size_t size) {
  for (size_t i = 0; i < size; i += 2) {
    float sig = noise.Process();
    for (size_t chn = 0; chn < 4; chn++) {
      out[chn][i] = sig;
    }
  }
}
void NoiseDroplet::Draw(int* d, int width, int height) {}
