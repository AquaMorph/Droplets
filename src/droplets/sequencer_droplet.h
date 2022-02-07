#pragma once

#ifndef DROPLETS_SEQUENCER_DROPLET_H_
#define DROPLETS_SEQUENCER_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

#define MAX_SEQUENCE_LENGTH 32
#define CONTROL_DEADZONE 0.00499f
#define CONTROL_RATE_LIMIT 25
#define NUM_ROWS 6

class SequencerDroplet: public Droplet {
private:
  int step = 0;
  int selected = 0;
  int sequence_length = 16;
  int num_columns = 4;
  int num_rows = NUM_ROWS;
  int control_rate_count = 0;
  float sequence[MAX_SEQUENCE_LENGTH] = { 0.0f };
  Parameter control[4];
  float last_control_value[4] = { 0.0f };

  /*
   * Set the sequencer to the next step.
   */
  void Step();

  /*
   * Reset the sequencers to the first step of the sequence.
   */
  void Reset();

  void SetColumns();

  void AdjustSelected(int adj);

  bool InMenu();
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
