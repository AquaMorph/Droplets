#pragma once

#ifndef DROPLETS_LFO_DROPLET_H_
#define DROPLETS_LFO_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"
#include "../graphics/graph.h"

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
  /*
   * Constructor for a LFO.
   *
   * @param m_patch pointer to patch
   * @param sample_rate audio sample rate
   * @param freqKnob frequence knob
   * @param ampKnob amp knob
   */
  void Init(DaisyPatch* m_patch,
	    float sample_rate,
	    AnalogControl freqKnob,
	    AnalogControl ampKnob);

  /*
   * Send LFO signal to the given channel.
   *
   * @param chn output channel
   */
  void Process(DacHandle::Channel chn);

  /*
   * Shift the wavestate.
   *
   * @param change amount to shift the waveshape
   */
  void UpdateWave(int change);

  /*
   * Returns the current waveshape of the LFO.
   *
   * @return lfo waveshape
   */
  uint8_t GetWave();

  /*
   * Returns LFO signal from 0,0 to 1.0.
   *
   * @return LFO signal
   */
  float GetSignal();
};

class LFODroplet: public Droplet {
private:
  LFO    lfo[2];
  Graph* title_graph;

  /*
   * Create a new graph for the title bar.
   */
  void CreateTitleGraph();

public:
  /*
   * Constructor for a LFO droplet.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   * @param sample_rate audio sample rate
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
