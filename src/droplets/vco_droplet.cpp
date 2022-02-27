#include "vco_droplet.h"

VCODroplet::VCODroplet(DaisyPatch* m_patch,
		       DropletState m_state,
		       float sample_rate) :
  Droplet(m_patch,
	  m_state) {
  SetAnimationRate(10);
  osc.Init(sample_rate);

  wave = Oscillator::WAVE_SAW;

  SetControls();
}

VCODroplet::~VCODroplet() {
  delete wave_graphic;
}

void VCODroplet::Control() {
  Patch()->ProcessAnalogControls();
  Patch()->encoder.Debounce();
  AdjustWaveShape(Patch()->encoder.Increment());
}

void VCODroplet::Process(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size) {
  float sig, freq, amp = 1.0;
  
  Patch()->ProcessAnalogControls();
  
  for (size_t i = 0; i < size; i++) {
    // Read Knobs
    freq = mtof(freqctrl.Process() + finectrl.Process());
    if (IsFull()) {
      if((size_t) wavectrl.Process() != last_wave_ctrl) {
	AdjustWaveShape((size_t)wavectrl.Process()-last_wave_ctrl);
	last_wave_ctrl = wavectrl.Process();
      }
      amp = ampctrl.Process();
    }
    // Set osc params
    osc.SetFreq(freq);
    osc.SetWaveform(wave);
    osc.SetAmp(amp);
    // Process
    sig = osc.Process();
    // Assign Synthesized Waveform to outputs.
    for (size_t chn = GetChannelMin(); chn < GetChannelMax(); chn++) {
      out[chn][i] = sig;
    }
  }
}

void VCODroplet::Draw() {
  SetWaveState(wave);
  if (IsFull()) {
    WriteCenteredString(Patch(),
			(GetScreenMax()-GetScreenMin())/2,
			54,
			Font_6x8,
			WaveToString(wave));
  } else {
    WriteDoubleCentered(Patch(),
			GetScreenMin() +
			(GetScreenMax()-GetScreenMin())/2,
			54,
			GetScreenMax()-GetScreenMin(),
			Font_6x8,
			WaveToString(wave));
  }
  wave_graphic->DrawTile(Patch(),
		 GetScreenMin(),
		 0,
		 GetScreenMax(),
		 GetTitleHeight());
  if(NeedUpdate()) {
    wave_graphic->AdjustXShift(1);
  }
  DrawName("VCO");
  AnimationInc();
}

void VCODroplet::SetWaveState(uint8_t wf) {
  switch(wf){
  case Oscillator::WAVE_TRI:
    wave_graphic->SetWaveShape(WaveShape::kTriangle);
    return;
  case Oscillator::WAVE_SQUARE:
    wave_graphic->SetWaveShape(WaveShape::kSquare);
    return;
  case Oscillator::WAVE_SIN:
    wave_graphic->SetWaveShape(WaveShape::kSine);
    return;
  case Oscillator::WAVE_SAW:
    wave_graphic->SetWaveShape(WaveShape::kSaw);
    return;
  case Oscillator::WAVE_RAMP:
    wave_graphic->SetWaveShape(WaveShape::kRamp);
    return;
  case Oscillator::WAVE_POLYBLEP_TRI:
    wave_graphic->SetWaveShape(WaveShape::kTriangle);
    return;
  case Oscillator::WAVE_POLYBLEP_SQUARE:
    wave_graphic->SetWaveShape(WaveShape::kSquare);
    return;
  default:
  case Oscillator::WAVE_POLYBLEP_SAW:
    wave_graphic->SetWaveShape(WaveShape::kSaw);
    return;
  }
}

void VCODroplet::AdjustWaveShape(int amount) {
  wave = (Oscillator::WAVE_LAST + wave + amount) %
    Oscillator::WAVE_LAST;
}

void VCODroplet::SetWaveShape(int ws) {
  wave = ws % Oscillator::WAVE_LAST;
  last_wave_ctrl = ws;
}

void VCODroplet::UpdateStateCallback() {
  SetControls();
}

void VCODroplet::SetControls() {
  DaisyPatch::Ctrl freq, fine;
  switch (GetState()){
  default:
  case DropletState::kFull:  
    wavectrl.Init(Patch()->controls[Patch()->CTRL_3],
		  0.0,
		  Oscillator::WAVE_LAST,
		  Parameter::LINEAR);
    ampctrl.Init(Patch()->controls[Patch()->CTRL_4],
		 0.0,
		 0.5f,
		 Parameter::LINEAR);
    freq = Patch()->CTRL_1;
    fine = Patch()->CTRL_2;
    SetWaveShape(wavectrl.Process());
    break;
  case DropletState::kLeft:
    freq = Patch()->CTRL_1;
    fine = Patch()->CTRL_2;
    break;
  case DropletState::kRight:
    freq = Patch()->CTRL_3;
    fine = Patch()->CTRL_4;
    break;
  }
  freqctrl.Init(Patch()->controls[freq], 10.0,
		110.0f, Parameter::LINEAR);
  finectrl.Init(Patch()->controls[fine], 0.f,
		7.f, Parameter::LINEAR);
}
