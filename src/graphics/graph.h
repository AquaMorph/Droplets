#pragma once

#ifndef DROPLETS_GRAPHICS_GRAPH_H
#define DROPLETS_GRAPHICS_GRAPH_H

#include "daisy_patch.h"
#include "../util.h"

using namespace daisy;

class Graph {
 private:
  int width, height, active;
  bool** graph;
  int GetNextActive();
 public:
  /*
   * Contsturctor for graph.
   * 
   * @param m_width width
   * @param m_height height
   */
  Graph(int m_width,
	int m_height);
  /*
   * Destructor for graph.
   */
  ~Graph();

  /*
   * Shifts the graph by one pixel.
   */
  void Update();

  /*
   * Clears the pxiels at the currently active column.
   */
  void ClearColumn();

  /*
   * Draws an active pixel on the graph.
   * 
   * @param pos y dimension of pixel
   */
  void SetPixel(int pos);

  /*
   * Draws a pixel on the graph.
   * 
   * @param pos y dimension of pixel
   * @param on pixel active state
   */
  void SetPixel(int pos, bool on);

  /*
   * Draws an acive pixel based on a percentage of the 
   * the height of the graph.
   *
   * @param percentage precentage height of the pixel
   */
  void SetPixelPercentage(double percentage);

  /*
   * Draws a pixel based on a percentage of the 
   * the height of the graph.
   *
   * @param percentage precentage height of the pixel
   * @param on pixel active state
   */
  void SetPixelPercentage(double percentage, bool on);

  /*
   * Draws graph on display.
   * 
   * @param patch daisy patch board
   * @param x starting x coordinate of graph
   * @param y starting y coordinate of graph
   */
  void Draw(DaisyPatch* patch, int x, int y);
};

#endif // DROPLETS_GRAPHICS_GRAPH_H
