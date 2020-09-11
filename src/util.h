#pragma once

#ifndef CASCADE_UTIL_H_
#define CASCADE_UTIL_H_

#include "daisy_patch.h"

#include <string>

using namespace daisy;

void DrawSolidRect(DaisyPatch,
		   uint8_t,
		   uint8_t,
		   uint8_t,
		   uint8_t,
		   bool);

void WriteString(DaisyPatch,
		 int,
		 int,
		 FontDef,
		 std::string,
		 bool);

void WriteString(DaisyPatch,
		 int,
		 int,
		 FontDef,
		 std::string);

#endif // CASCADE_UTIL_H_
