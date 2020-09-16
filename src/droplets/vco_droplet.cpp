#include "vco_droplet.h"

VCODroplet::VCODroplet(DaisyPatch* m_patch,
		       float sample_rate,
		       DropletState m_state) {
  UpdateState(m_state);
  patch = m_patch;
  int num_waves = Oscillator::WAVE_LAST - 1;
  osc.Init(sample_rate);
  freqctrl.Init(patch->controls[patch->CTRL_1], 10.0,
		110.0f, Parameter::LINEAR);
  finectrl.Init(patch->controls[patch->CTRL_2], 0.f,
		7.f, Parameter::LINEAR);
  wavectrl.Init(patch->controls[patch->CTRL_3], 0.0,
		num_waves, Parameter::LINEAR);
  ampctrl.Init(patch->controls[patch->CTRL_4], 0.0,
	       0.5f, Parameter::LINEAR);
}

void VCODroplet::Control() {}

void VCODroplet::Process(float** in, float** out, size_t size) {
  float sig, freq, amp;
  size_t wave;
  
  patch->UpdateAnalogControls();
  
  for (size_t i = 0; i < size; i += 2) {
    // Read Knobs
    freq = mtof(freqctrl.Process() + finectrl.Process());
    wave = wavectrl.Process();
    amp = ampctrl.Process();
    // Set osc params
    
    osc.SetFreq(freq);
    osc.SetWaveform(wave);
    osc.SetAmp(amp);
    // Process
    sig = osc.Process();
    // Assign Synthesized Waveform to all four outputs.
    for (size_t chn = 0; chn < 4; chn++) {
      out[chn][i] = sig;
    }
  }
}

void VCODroplet::Draw() {
  DrawName(patch, "VCO");
}
