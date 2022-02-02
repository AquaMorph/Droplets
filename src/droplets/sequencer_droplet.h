#pragma once

#ifndef DROPLETS_SEQUENCER_DROPLET_H_
#define DROPLETS_SEQUENCER_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

class SequencerDroplet: public Droplet {
private:
  int sequence_length = 32;
  int step = 0;
  float swquence[32] = { 0.0f };
public:
  /*
   * Constructor for a droplet.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   * @param sample_rate audio sample rate
   */
  SequencerDroplet(DaisyPatch* m_patch,
		  DropletState m_state,
		  float sample_rate);

  /*
   * Destructor for sequencer droplet.
   */
  ~SequencerDroplet();

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

#endif // DROPLETS_SEQUENCER_DROPLET_H_
