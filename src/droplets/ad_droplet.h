#pragma once

#ifndef DROPLETS_AD_DROPLET_H_
#define DROPLETS_AD_DROPLET_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"
#include "../graphics/graph.h"

using namespace daisy;
using namespace daisysp;

class AD {
private:
  AdEnv         env;
  float         attack, decay, curve = 0;
  float         amp = 1.0f;
  Parameter     attack_param;
  Parameter     decay_param;
  Parameter     curve_param;
  Parameter     amp_param;
  float         sig;
  DaisyPatch*   patch;
  bool          curve_menu = false;
  DropletState* state;
  
public:
  /*
   * Contructor for attach decay envelope.
   *
   * @param m_patch pointer to patch
   * @param sample_rate audio sample rate
   * @param state droplet position
   */
  void Init(DaisyPatch* m_patch,
	    float sample_rate,
	    DropletState* state);

  /*
   * Precesses input from the trigger gate
   * and sends envelope data to a given CV output.
   *
   * @param chn
   * @param gate
   */
  void Process(DacHandle::Channel chn,
	       DaisyPatch::GateInput gate);

  /*
   * Returns the envelope signal level.
   *
   * @return envelope signal level
   */
  float GetSignal();

  /*
   * Returns the envelope attack time.
   *
   * @return envelope attack time
   */
  float GetAttack();

  /*
   * Returns the envelope decay time.
   *
   * @return envelope decay time
   */
  float GetDecay();

  /*
   * Returns the envelope slope shape.
   *
   * @return envelope slope shape
   */
  float GetCurve();

  /*
   * Returns the envelope amp level.
   *
   * @return envelope amp level
   */
  float GetAmp();

  /*
   * Returns the envelope menu state.
   *
   * @return envelope menu state
   */
  bool GetMenu();

  /*
   * Toggles envelope menu state.
   */
  void ToggleCurve();

  /*
   * Binds envelope to menu hardware controls.
   */
  void SetControls();
};

class ADDroplet: public Droplet {
private:
  AD ad[2];
  float sample_rate;
  Graph* title_graph;

  /*
   * Create a new graph for the title bar.
   */
  void CreateTitleGraph();

public:
  /*
   * Constructor for a AD droplet.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   * @param sample_rate audio sample rate
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
  
  /*
   * Runs when droplet state is updated.
   */
  void UpdateStateCallback();
};

#endif // DROPLETS_AD_DROPLET_H_
