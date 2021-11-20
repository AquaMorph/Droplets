#pragma once

#ifndef DROPLETS_LFO_DROPLET_H_
#define DROPLETS_LFO_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

using namespace daisy;
using namespace daisysp;

#define MAX_WAVE Oscillator::WAVE_POLYBLEP_TRI

class LFO {
private:
  Oscillator  osc;
  Parameter   freqCtrl;
  Parameter   ampCtrl;
  float       amp;
  float       freq;
  uint8_t     wave;
  float       value;
  DaisyPatch* patch;
public:
  void Init(DaisyPatch* m_patch,
	    float samplerate,
	    AnalogControl freqKnob,
	    AnalogControl ampKnob);

  void Process(DacHandle::Channel chn);

  void UpdateWave(int change);
  
  uint8_t GetWave();
};

class LFODroplet: public Droplet {
private:
  LFO lfo[2];

public:
  /*
   * Constructor for a LFO droplet.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   */
  LFODroplet(DaisyPatch* m_patch,
	     DropletState m_state,
	     float sample_rate);
  
  /*
   * Destructor for vco droplet.
   */
  ~LFODroplet();

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

#endif // DROPLETS_LFO_DROPLET_H_
