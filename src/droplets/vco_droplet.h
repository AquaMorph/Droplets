#pragma once

#ifndef CASCADE_DROPLETS_VCO_DROPLET_H_
#define CASCADE_DROPLETS_VCO_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

using namespace daisy;
using namespace daisysp;

class VCODroplet: public Droplet {
 private:
  Oscillator osc;
  Parameter freqctrl, wavectrl, ampctrl, finectrl;
  std::string WaveToString(uint8_t);
 public:
  VCODroplet(DaisyPatch*, float, DropletState);
  void Control();
  void Process(float**, float**, size_t);
  void Draw();
};

#endif // CASCADE_DROPLETS_VCO_DROPLET_H_
