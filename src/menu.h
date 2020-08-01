#pragma once

#include "daisy_patch.h"
#include "util.h"

#include <string>

using namespace daisy;

class Menu {
 private:
  DaisyPatch* patch;
  Util* util;
 public:
  Menu(DaisyPatch*, Util*);
  bool InMenu();
  void SetInMenu(bool);
  void FilterMenuSelection();
  std::string FilterMenuText(int);
  void CreateMenuItem(std::string, int, bool);
  void ProcessMenuOled();
  void UpdateMenuPosition();
  std::string SelectedName();
};
