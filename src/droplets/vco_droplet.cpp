#include "vco_droplet.h"

VCODroplet::VCODroplet(DaisyPatch* m_patch,
		       DropletState m_state,
		       float sample_rate) :
  Droplet(m_patch,
	  m_state) {
  int num_waves = Oscillator::WAVE_LAST;
  SetAnimationRate(10);
  osc.Init(sample_rate);
  freqctrl.Init(Patch()->controls[Patch()->CTRL_1], 10.0,
		110.0f, Parameter::LINEAR);
  finectrl.Init(Patch()->controls[Patch()->CTRL_2], 0.f,
		7.f, Parameter::LINEAR);
  wavectrl.Init(Patch()->controls[Patch()->CTRL_3], 0.0,
		num_waves, Parameter::LINEAR);
  ampctrl.Init(Patch()->controls[Patch()->CTRL_4], 0.0,
	       0.5f, Parameter::LINEAR);
}

VCODroplet::~VCODroplet() {
  //  delete wave;
}

void VCODroplet::Control() {}

void VCODroplet::Process(float** in, float** out, size_t size) {
  float sig, freq, amp;
  size_t wave;
  
  Patch()->UpdateAnalogControls();
  
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
  WriteString(*Patch(), 0, 54, Font_6x8,
	      WaveToString(wavectrl.Process()));
  SetWaveState(wavectrl.Process());
  wave->DrawTile(*Patch(), GetScreenMin(), 0, GetScreenMax(), GetTitleHeight());
  if(NeedUpdate()) {
    wave->AdjustXShift(1);
  }
  DrawName("VCO");
  AnimationInc();
}

std::string VCODroplet::WaveToString(uint8_t wf) {
  switch(wf){
  case Oscillator::WAVE_TRI:
    return "Triangle";
  case Oscillator::WAVE_SQUARE:
    return "Square";
  case Oscillator::WAVE_SIN:
    return "Sine";
  case Oscillator::WAVE_SAW:
    return "Saw";
  case Oscillator::WAVE_RAMP:
    return "Ramp";
  case Oscillator::WAVE_POLYBLEP_TRI:
    return "Poly Triangle";
  case Oscillator::WAVE_POLYBLEP_SQUARE:
    return "Poly Square";
  case Oscillator::WAVE_POLYBLEP_SAW:
    return "Poly Saw";
  }
  return "";
}

void VCODroplet::SetWaveState(uint8_t wf) {
  switch(wf){
  case Oscillator::WAVE_TRI:
    wave->SetWaveShape(WaveShape::kTriangle);
    return;
  case Oscillator::WAVE_SQUARE:
    wave->SetWaveShape(WaveShape::kSquare);
    return;
  case Oscillator::WAVE_SIN:
    wave->SetWaveShape(WaveShape::kSine);
    return;
  case Oscillator::WAVE_SAW:
    wave->SetWaveShape(WaveShape::kSaw);
    return;
  case Oscillator::WAVE_RAMP:
    wave->SetWaveShape(WaveShape::kRamp);
    return;
  case Oscillator::WAVE_POLYBLEP_TRI:
    wave->SetWaveShape(WaveShape::kTriangle);
    return;
  case Oscillator::WAVE_POLYBLEP_SQUARE:
    wave->SetWaveShape(WaveShape::kSquare);
    return;
  default:
  case Oscillator::WAVE_POLYBLEP_SAW:
    wave->SetWaveShape(WaveShape::kSaw);
    return;
  }
}
