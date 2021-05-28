#pragma once

#ifndef CASCADE_DROPLETS_VCO_DROPLET_H_
#define CASCADE_DROPLETS_VCO_DROPLET_H_

#include <cmath>

#include "daisysp.h"
#include "daisy_patch.h"

#include "droplet.h"
#include "../util.h"
#include "../graphics/wave.h"

using namespace daisy;
using namespace daisysp;

class VCODroplet: public Droplet {
private:
  Oscillator osc;
  Parameter freqctrl, wavectrl, ampctrl, finectrl;
  size_t wave;
  size_t last_wave_ctrl;
  const double pi = std::acos(-1);
  Wave* wave_graphic = new Wave(WaveShape::kTriangle, 21, GetTitleHeight());

  /*
   * Converts oscilator to name of wave shape.
   *
   * @param wf wave shape
   * @return name of wave shap
   */
  std::string WaveToString(uint8_t wf);

  /*
   * Sets the vco wave shap to display on screen.
   *
   * @param wf wave shape
   */
  void SetWaveState(uint8_t wf);
public:
  /*
   * Constructor for voltage control oscillator droplet.
   *
   * @param m_patch pointer to patch
   * @param m_state droplet position
   * @param sample_rate audio sample rate
   */
  VCODroplet(DaisyPatch* m_patch,
	     DropletState m_state,
	     float sample_rate);
  
  /*
   * Destructor for vco droplet.
   */
  ~VCODroplet();

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
   * Changes the wave shape of the VCO.
   *
   * @param amount wave shape table position adjustment
   */
  void AdjustWaveShape(int amount);

  /*
   * Sets the wave shape of the VCO.
   *
   * @param ws wave shape
   */
  void SetWaveShape(int ws);
};

#endif // CASCADE_DROPLETS_VCO_DROPLET_H_
