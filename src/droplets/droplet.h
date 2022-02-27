#pragma once

#ifndef CASCADE_DROPLETS_DROPLET_H_
#define CASCADE_DROPLETS_DROPLET_H_

#include "daisy_patch.h"

#include <string>

#include "../util.h"

using namespace daisy;

enum class DropletState {kFull, kLeft, kRight};

class Droplet {
private:
  DaisyPatch* patch;
  DropletState state;
  const int kTitleHeight = 7;
  unsigned int count = 0;
  unsigned int animation_rate = 1;
  unsigned int animation_count = 0;
  int screen_min;
  int screen_max;
  size_t chn_min = 0;
  size_t chn_max = 4;
public:
  /*
   * Constructor for a droplet which is a mode for either half or full
   * control for the daisy patch.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   */
  Droplet(DaisyPatch* m_patch, DropletState m_state);

  /*
   * Destructor for a droplet.
   */
  virtual ~Droplet() {};

  /*
   * Processes user controls and inputs.
   */
  virtual void Control()=0;

  /*
   * Processes audio input and outputs.
2   *
   * @param in the audio inputs for the patch
   * @param out the audio outputs for the patch
   * @param size the number of inputs and outputs
   */
  virtual void Process(AudioHandle::InputBuffer in,
		       AudioHandle::OutputBuffer out,
		       size_t size)=0;

  /*
   * Processes information to be shown on the display. 
   */
  virtual void Draw()=0;

  /*
   * Runs when droplet state is updated.
   */
  virtual void UpdateStateCallback() {}

  /*
   * Set up the controls for the droplet.
   */
  virtual void SetControls() {}

  /*
   * Returns patch.
   *
   * @return pointer to patch
   */
  DaisyPatch* Patch();

  /*
   * Returns droplet state.
   *
   * @return pointer to state
   */
  DropletState* State();

  /*
   * Returns the size of the droplet.
   *
   * @return size of droplet
   */
  DropletState GetState();

  /*
   * Returns if the droplet is in the left state.
   *
   * @ return droplet in left state
   */
  bool IsLeft();

  /*
   * Returns if the droplet is in the right state.
   *
   * @ return droplet in right state
   */
  bool IsRight();

  /*
   * Returns if the droplet is in the full state.
   *
   * @ return droplet in full state
   */
  bool IsFull();

  /*
   * Returns the height of the title bar of the droplet.
   *
   * @return height of title bar
   */
  int GetTitleHeight();

  /*
   * Returns the width of the droplet.
   *
   * @return screen width of the droplet
   */
  int GetScreenWidth();

  /*
   * Returns the minimum screen position based on droplet size.
   *
   * @return droplet minimum screen position
   */
  int GetScreenMin();

  /*
   * Returns the maximum screen position based on droplet size.
   *
   * @return droplet maximum screen position
   */
  int GetScreenMax();

  /*
   * Returns the minimum channel position based on droplet size.
   *
   * @return droplet minimum channel position
   */
  size_t GetChannelMin();

  /*
   * Returns the maximum channel position based on droplet size.
   *
   * @return droplet maximum channel position
   */
  size_t GetChannelMax();

  /*
   * Draws droplet name on the title bar.
   *
   * @param name droplet position
   */
  void DrawName(std::string name);

  /*
   * Changes droplet position.
   *
   * @param m_state droplet 
   */
  void UpdateState(DropletState m_state);

  /*
   * Updates animation clock.
   */
  void AnimationInc();

  /*
   * Sets animation refresh rate
   *
   * @param rate display refrash rate
   */
  void SetAnimationRate(int rate);

  /*
   * Returns a count for total amount of animation frames.
   *
   * @return animation count
   */
  int GetAnimationCount();

  /*
   * Returns if display needs a refresh.
   *
   * @return display in need of update
   */
  bool NeedUpdate();
};

#endif // CASCADE_DROPLETS_DROPLET_H_
