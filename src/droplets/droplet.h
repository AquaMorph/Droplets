#pragma once

#ifndef CASCADE_DROPLETS_DROPLET_H_
#define CASCADE_DROPLETS_DROPLET_H_

class Droplet {
 public:
  virtual ~Droplet() {};
  virtual void Control(float, float, float, float)=0;
  virtual void Process(float**, float**, size_t)=0;
  virtual void Draw(int*, int, int)=0;
};

#endif // CASCADE_DROPLETS_DROPLET_H_
