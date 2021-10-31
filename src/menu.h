#pragma once

#ifndef CASCADE_MENU_H_
#define CASCADE_MENU_H_

#include "daisy_patch.h"
#include "menu_item.h"
#include "util.h"
#include "droplets/droplet_manager.h"

#include <string>

using namespace daisy;

const int MAX_CHAR_LENGTH = 15;
const int MENU_X[] = {0,  5,  10,  5,  0};
const int MENU_Y[] = {0, 11,  22, 41, 52};

class Menu {
 private:
  DaisyPatch* patch;
  DropletManager* manager;
  DropletState state;
  MenuItem* selected;
  MenuItem* buffer;
  MenuItem* highlighted;
  MenuItem* head;
  bool inMenu = false;

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
 public:
  /*
   * Constructor for a menu system to control the state of the patch.
   *
   * @param m_patch pointer to patch
   * @param m_name name of the menu
   * @param m_split one or two droplets
   */
  Menu(DaisyPatch* m_patch, DropletState m_state, DropletManager* m_manager);

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
