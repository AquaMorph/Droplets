#include "menu.h"

Menu::Menu(DaisyPatch* m_patch,
	   DropletState m_state,
	   DropletManager* m_manager) {
  patch = m_patch;
  state = m_state;
  manager = m_manager;

  head = new MenuItem(MenuState::kSplit, "Split");
  head->AddItemEnd(new MenuItem(MenuState::kChange, ""));
  head->AddItemEnd(new MenuItem(MenuState::kAD, "AD"));
  head->AddItemEnd(new MenuItem(MenuState::kLadderFilter, "Ladder Filter"));
  head->AddItemEnd(new MenuItem(MenuState::kLFO, "LFO"));
  head->AddItemEnd(new MenuItem(MenuState::kMixer, "Mixer"));
  head->AddItemEnd(new MenuItem(MenuState::kNoise, "Noise"));
  head->AddItemEnd(new MenuItem(MenuState::kSequencer, "Sequencer"));
  head->AddItemEnd(new MenuItem(MenuState::kVCA, "VCA"));
  head->AddItemEnd(new MenuItem(MenuState::kVCO, "VCO"));
  
  selected = head;
  buffer = selected;
  highlighted = selected;

  if (state == DropletState::kLeft) {
    head->SetStateTitle(MenuState::kChange, "Right");
  } else if (state == DropletState::kRight) {
    head->SetStateTitle(MenuState::kChange, "Left");
  }
  this->UpdateMenuState();
}

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
  ptr = highlighted->GetPreviousVisible();
  if (ptr == NULL) {
    CreateMenuItem("", 2, false);
  } else {
    CreateMenuItem(ptr->GetTitle(), 2, false);
    ptr = ptr->GetPreviousVisible();
  }
    // Item 1
  if (ptr == NULL) {
    CreateMenuItem("", 1, false);
  } else {
    CreateMenuItem(ptr->GetTitle(), 1, false);
  }

  // Item 4
  ptr = highlighted->GetNextVisible();
  if (ptr == NULL) {
    CreateMenuItem("", 4, false);
  } else {
    CreateMenuItem(ptr->GetTitle(), 4, false);
    ptr = ptr->GetNextVisible();
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

void Menu::SetState(MenuState state) {
  MenuItem* ptr = head;
  while(ptr != NULL) {
    if (ptr->GetState() == state) {
      Select(ptr);
      return;
    }
  ptr = ptr->GetNext();
  }
}

MenuState Menu::GetBufferState() {
  return buffer->GetState();
}

void Menu::UpdateMenuState() {
  if (manager->GetSplitMode()) {
    head->SetStateVisibility(MenuState::kChange, true);
    head->SetStateTitle(MenuState::kSplit, "Merge");
  } else {
    head->SetStateVisibility(MenuState::kChange, false);
    head->SetStateTitle(MenuState::kSplit, "Split");
  }
}

void Menu::Select() {
  Select(highlighted);
}

void Menu::Select(MenuItem* item) {
  if (selected->GetState() != MenuState::kSplit ||
      selected->GetState() != MenuState::kChange) {
    buffer = selected;
  }

  selected = item;
}
