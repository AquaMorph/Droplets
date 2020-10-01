#include "droplet_manager.h"

void DropletManager::ToggleSplit() {
  split = !split;
}

bool DropletManager::GetSplitMode() {
  return split;
}
