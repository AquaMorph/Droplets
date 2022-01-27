#pragma once

#ifndef DROPLETS_LADDER_FILTER_DROPLET_H_
#define DROPLETS_LADDER_FILTER_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

class LadderFilterDroplet: public Droplet {
private:
  MoogLadder filter[4];
  Parameter freq_ctrl, res_ctrl;
  float freq, res;
public:
  /*
   * Constructor for a droplet.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   * @param sample_rate audio sample rate
   */
  LadderFilterDroplet(DaisyPatch* m_patch,
		      DropletState m_state,
		      float sample_rate);

  /*
   * Processes user controls and inputs.
   */
  void Control();

  /*
   * Processes audio input and outputs.
   *
   * @param in the audio inputs for the patch
   * @param out the audio outputs for the patch
   * @param size the number of inputs and outputs
   */
  void Process(AudioHandle::InputBuffer in,
	       AudioHandle::OutputBuffer out,
	       size_t size);

  /*
   * Processes information to be shown on the display. 
   */
  void Draw();
  
  /*
   * Runs when droplet state is updated.
   */
  void UpdateStateCallback();

  /*
   * Set up the controls for the droplet.
   */
  void SetControls();
};

#endif // DROPLETS_LADDER_FILTER_DROPLET_H_
