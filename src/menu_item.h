#pragma once

#ifndef CASCADE_MENU_ITEM_H_
#define CASCADE_MENU_ITEM_H_

#include <string>

enum class MenuState {kSplit, kChange, kVCA, kVCO, kNoise};

class MenuItem {
 private:
  MenuState state;
  std::string title;
  bool visible;
  MenuItem* previous;
  MenuItem* next;
 public:
  MenuItem(MenuState m_state, std::string m_title);
  
  /*
   * Returns the title of the menu item.
   * 
   * @return menu item title
   */
  std::string GetTitle();

  /*
   * Sets the title for a munu item.
   * 
   * @param menu title
   */
  void SetTitle(std::string m_title);
  
  /*
   * Returns the previous menu item.
   * 
   * @return prvious menu item
   */
  MenuItem* GetPrevious();

  /*
   * Sets the previous menu item.
   *
   * @param previous menu item
   */
  void SetPrevious(MenuItem* item);

  /*
   * Returns the next menu item.
   *
   * @return next menu item
   */
  MenuItem* GetNext();
  /*
   * Sets the next menu item,
   *
   * @param next menu item
   */
  void SetNext(MenuItem* item);

  /*
   * Returns the previous visible menu item.
   *
   * @return previous visible munu item
   */
  MenuItem* GetPreviousVisible();

  /*
   * Returns the next visible menu item.
   *
   * @return next visible menu item
   */
  MenuItem* GetNextVisible();

  /*
   * Returns if the menu item is visible.
   *
   * @return visibility
   */
  bool IsVisible();

  /*
   * Sets the visibility of the menu item.
   *
   * @param visibility state
   */
  void SetVisibility(bool m_visible);

  /*
   * Toggles visibility of menu item.
   */
  void ToggleVisibility();

  /*
   * Set the visibility of all menu items with a given state.
   *
   * @param state
   * @param visibility
   */
  void SetStateVisibility(MenuState m_state, bool visibility);

  /*
   * Set the title of all menu items with a given state.
   *
   * @param state
   * @param title
   */
  void SetStateTitle(MenuState m_state, std::string m_title);

  /*
   * Returns the state of the menu item.
   *
   * @return state
   */
  MenuState GetState();

  /*
   * Add menu item before other menu item.
   *
   * @param menu item to be added
   */
  void AddItemBefore(MenuItem* item);

  /*
   * Add menu item after other menu item.
   *
   * @param menu item to be added
   */
  void AddItemAfter(MenuItem* item);

  /*
   * Add menu item at the beginning of a a menu item list.
   *
   * @param menu item to be added
   */
  void AddItemStart(MenuItem* item);

  /*
   * Add menu item at the end of a a menu item list.
   *
   * @param menu item to be added
   */
  void AddItemEnd(MenuItem* item);
};

#endif // CASCADE_MENU_ITEM_H_
