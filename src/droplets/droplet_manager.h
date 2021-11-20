#pragma once

#ifndef DROPLETS_DROPLET_MANAGER_H_
#define DROPLETS_DROPLET_MANAGER_H_

#include "droplet.h"

class DropletManager {
private:
  bool split = false;
  DropletState selected_drop = DropletState::kFull;
public:
  /*
   * Toggle droplet split mode.
   */
  void ToggleSplit();

  /*
   * Droplet split mode.
   *
   * @return droplet split mode state
   */
  bool GetSplitMode();

  /*
   * Set the currently selected droplet.
   *
   * @param selected droplet
   */
  void SetSelected(DropletState state);

  /*
   * Get the currently selected droplet.
   *
   * @return selected droplet
   */
  DropletState GetSelected();

  /*
   * Returns the name of the other droplet
   *
   * @param state droplat state of the current
   * @return other droplet name
   */
  std::string OtherStateName(DropletState state);
};

#endif // DROPLETS_DROPLET_MANAGER_H_

