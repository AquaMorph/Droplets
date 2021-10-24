#pragma once

#ifndef CASCADE_MENU_ITEM_H_
#define CASCADE_MENU_ITEM_H_

enum class MenuState {kSplit, kChange, kVCO, kNoise};

class MenuItem {
 private:
  MenuState state;
  char* title;
  bool visible;
  MenuItem* previous;
  MenuItem* next;
 public:
  MenuItem(MenuState m_state, char* m_title);
  
  /*
   * Returns the title of the menu item.
   * 
   * @return menu item title
   */
  char* GetTitle();

  /*
   * Sets the title for a munu item.
   * 
   * @param menu title
   */
  void SetTitle(char* m_title);
  
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
};

#endif // CASCADE_MENU_ITEM_H_
