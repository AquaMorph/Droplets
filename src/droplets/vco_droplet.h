#pragma once

#ifndef CASCADE_DROPLETS_VCO_DROPLET_H_
#define CASCADE_DROPLETS_VCO_DROPLET_H_

#include <cmath>

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"
#include "../graphics/wave.h"

using namespace daisy;
using namespace daisysp;

class VCODroplet: public Droplet {
private:
  Oscillator osc;
  Parameter freqctrl, wavectrl, ampctrl, finectrl;
  std::string WaveToString(uint8_t);
  void SetWaveState(uint8_t);
  const double pi = std::acos(-1);
  int sine_width = 21;
  Wave* wave = new Wave(WaveShape::kTriangle, sine_width, GetTitleHeight());
  int testH = 20;
  //Wave* testWave = new Wave(WaveShape::kSaw, 30, testH);
public:
  VCODroplet(DaisyPatch*, DropletState, float);
  ~VCODroplet();
  void Control();
  void Process(float**, float**, size_t);
  void Draw();
};

#endif // CASCADE_DROPLETS_VCO_DROPLET_H_
