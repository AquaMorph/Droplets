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
