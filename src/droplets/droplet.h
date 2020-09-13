#pragma once

#ifndef CASCADE_DROPLETS_DROPLET_H_
#define CASCADE_DROPLETS_DROPLET_H_

#include "daisy_patch.h"

using namespace daisy;

class Droplet {
 public:
  virtual ~Droplet() {};
  virtual void Control()=0;
  virtual void Process(float**, float**, size_t)=0;
  virtual void Draw()=0;
};

#endif // CASCADE_DROPLETS_DROPLET_H_
