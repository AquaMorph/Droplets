#include "menu.h"

Menu::Menu(DaisyPatch* m_patch,
	   DropletState m_state,
	   DropletManager* m_manager) {
  patch = m_patch;
  state = m_state;
  state = m_state;
}
const std::string MENU_ITEMS[] = {"TEST",
  "Change",
  "VCO", 
  "Noise"};
const int MENU_SIZE = sizeof(MENU_ITEMS)/sizeof(*MENU_ITEMS);
const int MAX_CHAR_LENGTH = 15;
const int MENU_X[] = {0,  5,  10,  5,  0};
const int MENU_Y[] = {0, 11,  22, 41, 52};
int selectedMenuItem = 0;
bool inMenu = false;

bool Menu::InMenu() {
  return inMenu;
}

void Menu::SetInMenu(bool menuState) {
  inMenu = menuState;
}

void Menu::FilterMenuSelection() {
  if (selectedMenuItem >= MENU_SIZE) {
    selectedMenuItem = MENU_SIZE - 1;
  } else if (selectedMenuItem < 0) {
    selectedMenuItem = 0;
  }
}

std::string Menu::FilterMenuText(int position) {
  if (position >= MENU_SIZE || position < 0) {
    return "";
  } else {
    if (ConvertState(position) == MenuState::kSplit) {
      if (!manager->GetSplitMode()) {
	return "Merge";
      } else {
	return "Split";
      }
    } else if (ConvertState(position) == MenuState::kChange) {
      return manager->OtherStateName(state);
    }
    return MENU_ITEMS[position];
  }
}

void Menu::CreateMenuItem(std::string text,
			  int position,
			  bool highlighted) {
  text.insert(text.end(), MAX_CHAR_LENGTH-text.size(), ' ');
  if (highlighted) {
    DrawSolidRect(patch, 0, MENU_Y[2],
		  SSD1309_WIDTH, MENU_Y[2]+17, true);
    WriteString(patch, MENU_X[position-1], MENU_Y[position-1],
		Font_11x18, text, !highlighted);
  } else {
    WriteString(patch, MENU_X[position-1], MENU_Y[position-1],
		Font_7x10, text, !highlighted);
  }
}

void Menu::ProcessMenuOled() {
  CreateMenuItem(FilterMenuText(selectedMenuItem-2), 1, false);
  CreateMenuItem(FilterMenuText(selectedMenuItem-1), 2, false);
  CreateMenuItem(FilterMenuText(selectedMenuItem),   3, true);
  CreateMenuItem(FilterMenuText(selectedMenuItem+1), 4, false);
  CreateMenuItem(FilterMenuText(selectedMenuItem+2), 5, false);
}

void Menu::UpdateMenuPosition() {
  selectedMenuItem -= patch->encoder.Increment();
  FilterMenuSelection();
}

std::string Menu::SelectedName() {
  return MENU_ITEMS[selectedMenuItem];
}

MenuState Menu::GetState() {
  return ConvertState(selectedMenuItem);
}

MenuState Menu::ConvertState(int menu_state) {
  return static_cast<MenuState>(menu_state);
}
