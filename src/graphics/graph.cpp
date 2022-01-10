#include "graph.h"

Graph::Graph(int m_width, int m_height) {
  width = m_width;
  height = m_height;
  graph = new bool*[width];
  for (int w = 0; w < width; w++) {
    graph[w] = new bool[height];
    for (int h = 0; h < height; h++) {
      graph[w][h] = false;
    }  
  }
  active = 0;
}

Graph::~Graph() {
  for (int w = 0; w < width; w++) {
    delete[] graph[w];
  }
  delete[] graph;
}

int Graph::GetNextActive() {
  if (active == width - 1) {
    return 0;
  } else {
    return active+1;
  }
}

void Graph::Update() {
  active = GetNextActive();
  ClearColumn();
}

void Graph::ClearColumn() {
  for (int h = 0; h < height; h++) {
    graph[active][h] = false;
  }
}

void Graph::SetPixel(int pos) {
  SetPixel(pos, true);
}

void Graph::SetPixel(int pos, bool on) {
  graph[active][pos] = on;
}

void Graph::SetPixelPercentage(double percentage) {
  SetPixelPercentage(percentage, true);
}

void Graph::SetPixelPercentage(double percentage, bool on) {
  SetPixel((int)(percentage*height), on);
}

void Graph::Draw(DaisyPatch* patch, int x, int y) {
  for (int w = 0; w < width; w++) {
    for (int h = 0; h < height; h++) {
      patch->display.DrawPixel(x+w, y+h,
			       graph[GetShiftArray(w, active, width)]
			       [GetShiftArray(height-h, height-1, height)]);
    }
  }
}
