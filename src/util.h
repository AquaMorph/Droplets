#include "daisy_patch.h"

#include <string>

using namespace daisy;

class Util {
 private:
  DaisyPatch* patch;
 public:
  Util(DaisyPatch*);
  
  void DrawSolidRect(uint8_t x1,
		     uint8_t y1,
		     uint8_t x2,
		     uint8_t y2,
		     bool on);

  void WriteString(int x,
		   int y,
		   std::string text);
};
