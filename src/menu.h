#pragma once

#ifndef CASCADE_MENU_H_
#define CASCADE_MENU_H_

#include "daisy_patch.h"
#include "util.h"

#include <string>

using namespace daisy;

class Menu {
 private:
  DaisyPatch* patch;
 public:
  Menu(DaisyPatch*);
  bool InMenu();
  void SetInMenu(bool);
  void FilterMenuSelection();
  std::string FilterMenuText(int);
  void CreateMenuItem(std::string, int, bool);
  void ProcessMenuOled();
  void UpdateMenuPosition();
  std::string SelectedName();
};

#endif // CASCADE_MENU_H_