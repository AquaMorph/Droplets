#pragma once

#ifndef CASCADE_MENU_H_
#define CASCADE_MENU_H_

#include "daisy_patch.h"
#include "util.h"

#include <string>

using namespace daisy;

enum class MenuState {kSplit, kChange, kVCO, kNoise};

class Menu {
 private:
  DaisyPatch* patch;
  bool* split;
  std::string name;

  /*
   * Converts a number to the related menu state.
   *
   * @param menu_state state number
   * @return menu state
   */
  MenuState ConvertState(int menu_state);
 public:
  /*
   * Constructor for a menu system to control the state of the patch.
   *
   * @param m_patch pointer to patch
   * @param m_name name of the menu
   * @param m_split one or two droplets
   */
  Menu(DaisyPatch* m_patch, std::string m_name, bool* m_split);

  /*
   * Gives if the user is currently in the menu.
   *
   * @return menu active
   */
  bool InMenu();

  /*
   * Sets if the user is in the menu.
   *
   * @param menu active
   */
  void SetInMenu(bool);

  /*
   * Keeps menu selection within the bounds of the menu's size.
   */
  void FilterMenuSelection();

  /*
   * Returns item name based on given position and if out of the menu
   * returns a blank string.
   *
   * @param position place in the menu
   * @return menu item name
   */
  std::string FilterMenuText(int position);

  /*
   * Draws a menu item on screen.
   *
   * @param text menu item name
   * @param position menu items position in the menu
   * @param highlighted state of menu items selection
   */
  void CreateMenuItem(std::string text,
		      int position,
		      bool highlighted);

  /*
   * Draws droplet information on the screen.
   */
  void ProcessMenuOled();

  /*
   * Updates menu position based on user input from the encoder.
   */
  void UpdateMenuPosition();

  /*
   * Returns the name of the currently selected menu item.
   *
   * @return selected menu item's name
   */
  std::string SelectedName();

  /*
   * Returns the currently selected menu item.
   *
   * @return menu state
   */
  MenuState GetState();
};

#endif // CASCADE_MENU_H_
