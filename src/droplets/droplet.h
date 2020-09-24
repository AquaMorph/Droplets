#pragma once

#ifndef CASCADE_DROPLETS_DROPLET_H_
#define CASCADE_DROPLETS_DROPLET_H_

#include "daisy_patch.h"

#include <string>

#include "../util.h"

using namespace daisy;

enum class DropletState {kFull, kLeft, kRight};

class Droplet {
private:
  DaisyPatch* patch;
  DropletState state;
  const int kTitleHeight = 7;
  unsigned int count = 0;
  unsigned int animation_rate = 1;
  unsigned int animation_count = 0;
  int screen_min;
  int screen_max;
  size_t chn_min = 0;
  size_t chn_max = 4;
public:
  Droplet(DaisyPatch*, DropletState);
  virtual ~Droplet() {};
  virtual void Control()=0;
  virtual void Process(float**, float**, size_t)=0;
  virtual void Draw()=0;
  DaisyPatch* Patch();
  DropletState GetState();
  int GetTitleHeight();
  int GetScreenMin();
  int GetScreenMax();
  size_t GetChannelMin();
  size_t GetChannelMax();
  void DrawName(std::string);
  void UpdateState(DropletState);  
  void AnimationInc();
  void SetAnimationRate(int);
  int GetAnimationCount();
  bool NeedUpdate();
};

#endif // CASCADE_DROPLETS_DROPLET_H_
