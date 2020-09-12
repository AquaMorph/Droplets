#pragma once

#ifndef CASCADE_DROPLETS_NOISE_DROPLET_H_
#define CASCADE_DROPLETS_NOISE_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"

class NoiseDroplet: public Droplet {
 private:
  daisysp::WhiteNoise noise;
 public:
  NoiseDroplet(float);
  void Control(float, float, float, float);
  void Process(float**, float**, size_t);
  void Draw(int*, int, int);
};

#endif // CASCADE_DROPLETS_NOISE_DROPLET_H_
