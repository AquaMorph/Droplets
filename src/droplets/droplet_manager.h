#pragma once

#ifndef CASCADE_DROPLETS_DROPLET_MANAGER_H_
#define CASCADE_DROPLETS_DROPLET_MANAGER_H_

class DropletManager {
private:
  bool split = false;
public:
  /*
   * Toggle droplet split mode.
   */
  void ToggleSplit();

  /*
   * Droplet split mode.
   */
  bool GetSplitMode();
};

#endif // CASCADE_DROPLETS_DROPLET_MANAGER_H_

