#pragma once

#ifndef CASCADE_DROPLETS_MIXER_DROPLET_H_
#define CASCADE_DROPLETS_MIXER_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

using namespace daisy;
using namespace daisysp;

class MixerDroplet: public Droplet {
private:
  Parameter mix[4];

public:
  /*
   * Constructor for a mixer droplet.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   */
  MixerDroplet(DaisyPatch* m_patch,
	     DropletState m_state);
  
  /*
   * Destructor for vco droplet.
   */
  ~MixerDroplet();

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
};

#endif // CASCADE_DROPLETS_VCA_DROPLET_H_
