#include "ad_droplet.h"

void AD::Init(DaisyPatch* m_patch,
	      float sample_rate,
	      AnalogControl attack_knob,
	      AnalogControl decay_knob) {
    patch = m_patch;
    env.Init(sample_rate);
    env.SetMax(1.0f);
    env.SetMin(0.0f);
    env.SetCurve(0.0f);
    attack_param.Init(attack_knob, .01f, 3.0f, Parameter::EXPONENTIAL);
    decay_param.Init(decay_knob, .01f, 3.0f, Parameter::EXPONENTIAL);
  }

void AD::Process(DacHandle::Channel chn,
		 DaisyPatch::GateInput gate) {
  if(patch->gate_input[gate].Trig()) {
    env.Trigger();
  }

  env.SetTime(ADENV_SEG_ATTACK, attack_param.Process());
  env.SetTime(ADENV_SEG_DECAY, decay_param.Process());
  
  sig = env.Process();
  patch->seed.dac.WriteValue(chn,
			     sig * 4095.0f);
}

float AD::GetSignal() {
  return sig;
}

ADDroplet::ADDroplet(DaisyPatch* m_patch,
		       DropletState m_state,
		       float sample_rate) :
  Droplet(m_patch,
	  m_state) {
  switch (GetState()) {
  default:
  case DropletState::kFull:
    ad[0].Init(Patch(),
		sample_rate,
		Patch()->controls[Patch()->CTRL_1],
		Patch()->controls[Patch()->CTRL_2]);
    ad[1].Init(Patch(),
		sample_rate,
		Patch()->controls[Patch()->CTRL_3],
		Patch()->controls[Patch()->CTRL_4]);
    break;
  case DropletState::kLeft:
    ad[0].Init(Patch(),
		sample_rate,
		Patch()->controls[Patch()->CTRL_1],
		Patch()->controls[Patch()->CTRL_2]);
    break;
  case DropletState::kRight:
    ad[0].Init(Patch(),
		sample_rate,
		Patch()->controls[Patch()->CTRL_3],
		Patch()->controls[Patch()->CTRL_4]);
    break;
  }
}

ADDroplet::~ADDroplet() {}

void ADDroplet::Control() {}

void ADDroplet::Process(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size) {
  Patch()->ProcessAnalogControls();

  for(size_t i = 0; i < size; i++) {
    if (GetState() == DropletState::kRight) {
      ad[0].Process(DacHandle::Channel::TWO, DaisyPatch::GATE_IN_2);
    } else {
      ad[0].Process(DacHandle::Channel::ONE, DaisyPatch::GATE_IN_1);
    }
    if (GetState() == DropletState::kFull) {
      ad[1].Process(DacHandle::Channel::TWO, DaisyPatch::GATE_IN_2);
    }
    int env_sel = 0;
    for (size_t chn = GetChannelMin(); chn < GetChannelMax(); chn++) {
      if(GetState() == DropletState::kFull && chn > 1) {
	env_sel = 1;
      }
      out[chn][i] = in[chn][i] * ad[env_sel].GetSignal();
    }
  }
}

void ADDroplet::Draw() {
  DrawName("AD");
}
