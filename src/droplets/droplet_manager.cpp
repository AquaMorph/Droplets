#include "droplet_manager.h"

void DropletManager::ToggleSplit() {
  split = !split;
}

bool DropletManager::GetSplitMode() {
  return split;
}

void DropletManager::SetSelected(DropletState state) {
  selected_drop = state;
}

DropletState DropletManager::GetSelected() {
  return selected_drop;
}

std::string DropletManager::OtherStateName(DropletState state) {
  switch (state) {
  case DropletState::kLeft:
    return "Right";
  case DropletState::kRight:
    return "Left";
  case DropletState::kFull:
  default:
    return "";
  }
}
