#pragma once

#ifndef CASCADE_DROPLETS_VCO_DROPLET_H_
#define CASCADE_DROPLETS_VCO_DROPLET_H_

#include <cmath>

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"
#include "../graphics/sprite.h"

using namespace daisy;
using namespace daisysp;

class VCODroplet: public Droplet {
private:
  Oscillator osc;
  Parameter freqctrl, wavectrl, ampctrl, finectrl;
  std::string WaveToString(uint8_t);
  const double pi = std::acos(-1);
  int sine_width = 20;
  Sprite* wave = new Sprite(sine_width, kTitleHeight);
public:
  VCODroplet(DaisyPatch*, DropletState, float);
  ~VCODroplet();
  void Control();
  void Process(float**, float**, size_t);
  void Draw();
};

#endif // CASCADE_DROPLETS_VCO_DROPLET_H_
