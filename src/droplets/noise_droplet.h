#pragma once

#ifndef DROPLETS_NOISE_DROPLET_H_
#define DROPLETS_NOISE_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

class NoiseDroplet: public Droplet {
private:
  daisysp::WhiteNoise noise;
public:
  /*
   * Constructor for a droplet which outputs noise.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   */
  NoiseDroplet(DaisyPatch*, DropletState);

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
};

#endif // DROPLETS_NOISE_DROPLET_H_
