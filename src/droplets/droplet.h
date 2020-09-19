#pragma once

#ifndef CASCADE_DROPLETS_DROPLET_H_
#define CASCADE_DROPLETS_DROPLET_H_

#include "daisy_patch.h"

#include <string>

#include "../util.h"

using namespace daisy;

enum class DropletState {kFull, kLeft, kRight};

class Droplet {
 public:
  DaisyPatch* patch;
  DropletState state;
  Droplet(DaisyPatch*, DropletState);
  virtual void Control()=0;
  virtual void Process(float**, float**, size_t)=0;
  virtual void Draw()=0;
  const int kTitleHeight = 8;
  int screen_min;
  int screen_max;
  size_t chn_min = 0;
  size_t chn_max = 4;
  void DrawName(daisy::DaisyPatch*,
		std::string);
  void UpdateState(DropletState);
};

#endif // CASCADE_DROPLETS_DROPLET_H_
