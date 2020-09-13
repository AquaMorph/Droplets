#pragma once

#ifndef CASCADE_DROPLETS_NOISE_DROPLET_H_
#define CASCADE_DROPLETS_NOISE_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

class NoiseDroplet: public Droplet {
 private:
  DaisyPatch* patch;
  daisysp::WhiteNoise noise;
  daisysp::NlFilt filter;
 public:
  NoiseDroplet(DaisyPatch*, float, DropletState);
  void Control();
  void Process(float**, float**, size_t);
  void Draw();
};

#endif // CASCADE_DROPLETS_NOISE_DROPLET_H_
