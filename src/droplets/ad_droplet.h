#pragma once

#ifndef CASCADE_DROPLETS_AD_DROPLET_H_
#define CASCADE_DROPLETS_AD_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"

using namespace daisy;
using namespace daisysp;

class AD {
private:
  AdEnv         env;
  float         attack, decay, curve = 0;
  Parameter     attack_param;
  Parameter     decay_param;
  Parameter     curve_param;
  float         sig;
  DaisyPatch*   patch;
  bool          curve_menu = false;
public:
  void Init(DaisyPatch* m_patch,
	    float sample_rate,
	    AnalogControl attack_knob,
	    AnalogControl decay_knob);

  void Process(DacHandle::Channel chn, DaisyPatch::GateInput gate);

  float GetSignal();
  float GetAttack();
  float GetDecay();
  float GetCurve();
  bool GetMenu();
  void ToggleCurve();
};

class ADDroplet: public Droplet {
private:
  AD ad[2];

public:
  /*
   * Constructor for a AD droplet.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   */
  ADDroplet(DaisyPatch* m_patch,
	     DropletState m_state,
	     float sample_rate);
  
  /*
   * Destructor for vco droplet.
   */
  ~ADDroplet();

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

#endif // CASCADE_DROPLETS_AD_DROPLET_H_
