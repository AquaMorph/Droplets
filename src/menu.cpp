#include "menu.h"

Menu::Menu(DaisyPatch* m_patch,
	   DropletState m_state,
	   DropletManager* m_manager) {
  patch = m_patch;
  state = m_state;
  manager = m_manager;

  head = new MenuItem(MenuState::kSplit, "Split");
  head->AddItemEnd(new MenuItem(MenuState::kChange, "Right"));
  head->AddItemEnd(new MenuItem(MenuState::kVCO, "VCO"));
  head->AddItemEnd(new MenuItem(MenuState::kNoise, "Noise"));
  selected = head;
  buffer = selected;
  highlighted = selected;
}
const std::string MENU_ITEMS[] = {"Split",
  "Change",
  "VCO", 
  "Noise"};
const int MENU_SIZE = sizeof(MENU_ITEMS)/sizeof(*MENU_ITEMS);
const int MAX_CHAR_LENGTH = 15;
const int MENU_X[] = {0,  5,  10,  5,  0};
const int MENU_Y[] = {0, 11,  22, 41, 52};

bool Menu::InMenu() {
  return this->inMenu;
}

void Menu::SetInMenu(bool menuState) {
  inMenu = menuState;
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
  MenuItem* ptr;
  // Item 3 Highlighted
  CreateMenuItem(highlighted->GetTitle(),   3, true);

  // Item 2
  ptr = highlighted->GetPrevious();
  if (ptr == NULL) {
    CreateMenuItem("", 2, false);
  } else {
    CreateMenuItem(ptr->GetTitle(), 2, false);
    ptr = ptr->GetPrevious();
  }
    // Item 1
  if (ptr == NULL) {
    CreateMenuItem("", 1, false);
  } else {
    CreateMenuItem(ptr->GetTitle(), 1, false);
  }

  // Item 4
  ptr = highlighted->GetNext();
  if (ptr == NULL) {
    CreateMenuItem("", 4, false);
  } else {
    CreateMenuItem(ptr->GetTitle(), 4, false);
    ptr = ptr->GetNext();
  }

  // Item 5
  if (ptr == NULL) {
    CreateMenuItem("", 5, false);
  } else {
    CreateMenuItem(ptr->GetTitle(), 5, false);
  }
}

void Menu::UpdateMenuPosition() {
  int move = patch->encoder.Increment();
  if (move < 0) {
    if (highlighted->GetNextVisible() != NULL) {
      highlighted = highlighted->GetNextVisible();
    }
  } else if (move > 0) {
    if (highlighted->GetPreviousVisible() != NULL) {
      highlighted = highlighted->GetPreviousVisible();
    }
  }
}

std::string Menu::SelectedName() {
  return highlighted->GetTitle();
}

MenuState Menu::GetState() {
  return highlighted->GetState();
}

