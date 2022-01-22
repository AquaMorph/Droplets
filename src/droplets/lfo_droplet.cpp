#include "lfo_droplet.h"

void LFO::Init(DaisyPatch* m_patch,
	    float samplerate,
	    AnalogControl freqKnob,
	    AnalogControl ampKnob) {
    patch = m_patch;
    osc.Init(samplerate);
    osc.SetAmp(1);
    wave = 0;
    freqCtrl.Init(freqKnob, 0.1f, 35.0f, Parameter::LOGARITHMIC);
    ampCtrl.Init(ampKnob, 0.0f, 1.0f, Parameter::LINEAR);
  }

void LFO::Process(DacHandle::Channel chn) {
  osc.SetFreq(freqCtrl.Process());
  osc.SetWaveform(wave);
  
  patch->seed.dac.WriteValue(chn,
			     GetSignal() * ampCtrl.Process() * 4095.f);
}

void LFO::UpdateWave(int change) {
  wave = (MAX_WAVE + wave + change) % MAX_WAVE;
}

uint8_t LFO::GetWave() {
  return wave;
}

float LFO::GetSignal() {
  return (osc.Process()+ 1.0f) /2;
}

LFODroplet::LFODroplet(DaisyPatch* m_patch,
		       DropletState m_state,
		       float m_sample_rate) :
  Droplet(m_patch,
	  m_state) {
  sample_rate = m_sample_rate;
  SetAnimationRate(5);
  CreateTitleGraph();
  SetControls();
}

LFODroplet::~LFODroplet() {
  delete title_graph;
}

void LFODroplet::CreateTitleGraph() {
  title_graph = new Graph(GetScreenMax()-GetScreenMin(),
			  GetTitleHeight());
}

void LFODroplet::Control() {
  Patch()->ProcessAnalogControls();
  Patch()->encoder.Debounce();
  lfo[0].UpdateWave(Patch()->encoder.Increment());
  if (GetState() == DropletState::kFull) {
    lfo[1].UpdateWave(Patch()->encoder.Increment());
  }
}

void LFODroplet::Process(AudioHandle::InputBuffer in,
			 AudioHandle::OutputBuffer out,
			 size_t size) {
  Patch()->ProcessAnalogControls();

  for(size_t i = 0; i < size; i++) {
    if (GetState() == DropletState::kRight) {
      lfo[0].Process(DacHandle::Channel::TWO);
    } else {
      lfo[0].Process(DacHandle::Channel::ONE);
    }
    if (GetState() == DropletState::kFull) {
      lfo[1].Process(DacHandle::Channel::TWO);
    }
  }
}

void LFODroplet::Draw() {
  if (GetState() == DropletState::kFull) {
    WriteCenteredString(Patch(),
			(GetScreenMax()-GetScreenMin())/2,
			54,
			Font_6x8,
			WaveToString(lfo[0].GetWave()));
  } else {
    WriteDoubleCentered(Patch(),
			GetScreenMin() +
			(GetScreenMax()-GetScreenMin())/2,
			54,
			GetScreenMax()-GetScreenMin(),
			Font_6x8,
			WaveToString(lfo[0].GetWave()));
  }

  if(NeedUpdate()) {
    title_graph->Update();
  }
  title_graph->SetPixelPercentage(lfo[0].GetSignal());
  title_graph->Draw(Patch(), GetScreenMin(), 0);
  
  DrawName("LFO");
  AnimationInc();
}

void LFODroplet::UpdateStateCallback() {
  delete title_graph;
  CreateTitleGraph();
  SetControls();
}

void LFODroplet::SetControls() {
  switch (GetState()) {
  default:
  case DropletState::kFull:
    lfo[0].Init(Patch(),
		sample_rate,
		Patch()->controls[Patch()->CTRL_1],
		Patch()->controls[Patch()->CTRL_2]);
    lfo[1].Init(Patch(),
		sample_rate,
		Patch()->controls[Patch()->CTRL_3],
		Patch()->controls[Patch()->CTRL_4]);
    break;
  case DropletState::kLeft:
    lfo[0].Init(Patch(),
		sample_rate,
		Patch()->controls[Patch()->CTRL_1],
		Patch()->controls[Patch()->CTRL_2]);
    break;
  case DropletState::kRight:
    lfo[0].Init(Patch(),
		sample_rate,
		Patch()->controls[Patch()->CTRL_3],
		Patch()->controls[Patch()->CTRL_4]);
    break;
  }
}
