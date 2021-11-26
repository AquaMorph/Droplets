#pragma once

#ifndef CASCADE_UTIL_H_
#define CASCADE_UTIL_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include <string>
#include <math.h>

using namespace daisy;
using namespace daisysp;

#define SSD1309_WIDTH 128

/*
 * Draws a solid rectangle on screen.
 *
 * @param patch daisy patch board
 * @param x1 x coordinate of the first point
 * @param y1 y coordinate of the first point
 * @param x2 x coordinate of the second point
 * @param y2 y coordinate of the second point 
 * @param on draw screen on or off
 */
void DrawSolidRect(DaisyPatch* patch,
		   uint8_t x1,
		   uint8_t y1,
		   uint8_t x2,
		   uint8_t y2,
		   bool on);

/*
 * Draws text on screen flushed left. 
 *
 * @param patch daisy patch board
 * @param x start of text x coordinate 
 * @param y start of text y coordinate
 * @param font text font
 * @param text text to be written
 * @param on draw screen on or off
 */
void WriteString(DaisyPatch* patch,
		 int x,
		 int y,
		 FontDef font,
		 std::string text,
		 bool on);

/*
 * Draws text on screen flushed left. 
 *
 * @param patch daisy patch board
 * @param x start of text x coordinate 
 * @param y start of text y coordinate
 * @param font text font
 * @param text text to be written
 */
void WriteString(DaisyPatch* patch,
		 int x,
		 int y,
		 FontDef font,
		 std::string text);

/*
 * Draws text on screen centered. 
 *
 * @param patch daisy patch board
 * @param x center of text x coordinate 
 * @param y start of text y coordinate
 * @param font text font
 * @param text text to be written
 * @param on draw screen on or off
 */
void WriteCenteredString(DaisyPatch* patch,
			 int x,
			 int y,
			 FontDef font,
			 std::string text,
			 bool on);

/*
 * Draws text on screen centered. 
 *
 * @param patch daisy patch board
 * @param x center of text x coordinate 
 * @param y start of text y coordinate
 * @param font text font
 * @param text text to be written
 */
void WriteCenteredString(DaisyPatch* patch,
			 int x,
			 int y,
			 FontDef font,
			 std::string text);

/*
 * Draws text on screen centered taking up two lines. 
 *
 * @param patch daisy patch board
 * @param x center of text x coordinate 
 * @param y start of text y coordinate
 * @param width text field width
 * @param font text font
 * @param text text to be written
 * @param on draw screen on or off
 */
void WriteDoubleCentered(DaisyPatch* patch,
			 int x,
			 int y,
			 int width,
			 FontDef font,
			 std::string text,
			 bool on);

/*
 * Draws text on screen centered taking up two lines. 
 *
 * @param patch daisy patch board
 * @param x center of text x coordinate 
 * @param y start of text y coordinate
 * @param width text field width
 * @param font text font
 * @param text text to be written
 */
void WriteDoubleCentered(DaisyPatch* patch,
			 int x,
			 int y,
			 int width,
			 FontDef font,
			 std::string text);

/*
 * Converts oscilator to name of wave shape.
 *
 * @param wf wave shape
 * @return name of wave shap
 */
std::string WaveToString(uint8_t wf);

/*
 * Converts float to formatted string.
 *
 * @param input number
 * @param number of decimal places
 */
std::string FloatToString(float num, int places);

/*
 * Draws two rectangles on the left and right side of a given area.
 *
 * @param patch daisy patch board
 * @param divider rectangle length
 * @param width_min left edge of bounding box
 * @param width_max right enge of bounding box
 * @param rect_one_min first rectangle lowest edge 
 * @param rect_one_max first rectangle highest edge
 * @param rect_two_min second rectangle lowest edge
 * @param rect_two_max second rectangle highest edge
 */
void DrawTwoDividedRectangles(DaisyPatch* patch,
				int divider,
				int width_min,
				int width_max,
				int rect_one_min,
				int rect_one_max,
				int rect_two_min,
				int rect_two_max);

/*
 * Draws four rectangles on the left and right side of a given area.
 *
 * @param patch daisy patch board
 * @param divider rectangle length
 * @param width_min left edge of bounding box
 * @param width_max right enge of bounding box
 * @param rect_one_min first rectangle lowest edge 
 * @param rect_one_max first rectangle highest edge
 * @param rect_two_min second rectangle lowest edge
 * @param rect_two_max second rectangle highest edge
 * @param rect_one_min third rectangle lowest edge 
 * @param rect_one_max third rectangle highest edge
 * @param rect_two_min forth rectangle lowest edge
 * @param rect_two_max forth rectangle highest edge
 */
void DrawFourDividedRectangles(DaisyPatch* patch,
			       int divider,
			       int width_min,
			       int width_max,
			       int rect_one_min,
			       int rect_one_max,
			       int rect_two_min,
			       int rect_two_max,
			       int rect_three_min,
			       int rect_three_max,
			       int rect_four_min,
			       int rect_four_max);

#endif // CASCADE_UTIL_H_
