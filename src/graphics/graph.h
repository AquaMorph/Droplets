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
  Graph(int m_width,
	int m_height);
  ~Graph();
  void Update();
  void ClearColumn();
  void SetPixel(int pos);
  void SetPixel(int pos, bool on);
  void SetPixelPercentage(double percentage);
  void SetPixelPercentage(double percentage, bool on);
  void Draw(DaisyPatch* patch, int x, int y);
};

#endif // DROPLETS_GRAPHICS_GRAPH_H
