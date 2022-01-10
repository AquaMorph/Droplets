#pragma once

#ifndef DROPLETS_GRAPHICS_SPRITE_H_
#define DROPLETS_GRAPHICS_SPRITE_H_

#include "daisy_patch.h"
#include "../util.h"

using namespace daisy;

class Sprite {
 private:
  int width, height;
  bool** sprite;
  int x_shift = 0;
  int y_shift = 0;

  /*
   * Converts a x axis position based upon the sprites shift.
   *
   * @param pos x axis position
   * @return new x axis position
   */
  int GetShiftArrayX(int pos);

  /*
   * Converts a y axis position based upon the sprites shift.
   *
   * @param pos y axis position
   * @return new y axis position
   */
  int GetShiftArrayY(int pos);
 public:
  /*
   * Contsturctor for sprite.
   * 
   * @param m_width width
   * @param m_height height
   */
  Sprite(int m_width,
	 int m_height);

  /*
   * Destructor for sprite.
   */ 
  ~Sprite();

  /*
   * Sets a pixel on the sprite.
   *
   * @param x pixel x coordinate
   * @param y pixel y coordinate
   * @param on pixel on or off
   */
  void AddPixel(int x,
		int y,
		bool on);

  /*
   * Adds a line to the sprite.
   * 
   * @param x1 x coordinate of the first point
   * @param y1 y coordinate of the first point
   * @param x2 x coordinate of the second point
   * @param y2 y coordinate of the second point
   * @param on line display on or off
   */
  void AddLine(int x1,
	       int y1,
	       int x2,
	       int y2,
	       bool on);

  /*
   * Returns the height of the sprite.
   *
   * @return sprite height
   */
  int GetHeight();

  /*
   * Returns the width of the sprite.
   * 
   * @return sprite width
   */
  int GetWidth();

  /*
   * Returns 2d array of booleans representing pixel state of sprite. 
   *
   * @return sprite graphic
   */
  bool** GetSprite();

  /*
   * Draws sprite on display.
   * 
   * @param patch daisy patch board
   * @param x starting x coordinate of sprite
   * @param y starting y coordinate of sprite
   */
  void Draw(DaisyPatch* patch,
	    int x,
	    int y);

  /*
   * Draws the sprite on the display where the sprite will form
   * a tile pattern when drawn on a canvus larger than the sprite.
   *
   * @param patch daisy patch board
   * @param x1 x coordinate of the first point
   * @param y1 y coordinate of the first point
   * @param x2 x coordinate of the second point
   * @param y2 y coordinate of the second point
   */
  void DrawTile(DaisyPatch* patch,
		int x1,
		int y1,
		int x2,
		int y2);
  /*
   * Sets sprite pixels to off.
   */
  void SetBlank();

  /*
   * Sets the x axis shift.
   *
   * @param x shift value for the x axis
   */
  void SetXShift(int x);

  /*
   * Sets the y axis shift.
   *
   * @param y shift value for the x axis
   */
  void SetYShift(int y);

  /*
   * Adjusts x axis shift by the given amount.
   *
   * @param x shift of x axis
   */
  void AdjustXShift(int x);

  /*
   * Adjusts y axis shift by the given amount.
   *
   * @param y shift of x axis
   */
  void AdjustYShift(int y);
};

#endif // DROPLETS_GRAPHICS_SPRITE_H_
