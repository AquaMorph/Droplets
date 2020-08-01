#pragma once

#include "daisy_patch.h"

#include <string>

using namespace daisy;

class Util {
 private:
  DaisyPatch* patch;
 public:
  Util(DaisyPatch*);
  
  void DrawSolidRect(uint8_t,
		     uint8_t,
		     uint8_t,
		     uint8_t,
		     bool);

  void WriteString(int,
		   int,
		   std::string);
};
