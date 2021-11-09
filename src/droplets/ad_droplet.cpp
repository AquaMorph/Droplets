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
    curve_param.Init(attack_knob, -10.f, 10.0f, Parameter::LINEAR);
  }

void AD::Process(DacHandle::Channel chn,
		 DaisyPatch::GateInput gate) {
  if(patch->gate_input[gate].Trig()) {
    env.Trigger();
  }
  if (curve_menu) {
    curve = curve_param.Process();
  } else {
    attack = attack_param.Process();
  }
  decay = decay_param.Process();
  env.SetTime(ADENV_SEG_ATTACK, attack);
  env.SetTime(ADENV_SEG_DECAY, decay);
  env.SetCurve(curve);
  
  sig = env.Process();
  patch->seed.dac.WriteValue(chn,
			     sig * 4095.0f);
}

float AD::GetSignal() {
  return sig;
}

float AD::GetAttack() {
  return attack;
}

float AD::GetDecay() {
  return decay;
}

float AD::GetCurve() {
  return curve;
}

bool AD::GetMenu() {
  return curve_menu;
}

void AD::ToggleCurve() {
  curve_menu = !curve_menu;
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

void ADDroplet::Control() {
  if (Patch()->encoder.Pressed()) {
    if (Patch()->encoder.TimeHeldMs() < 10) {
      ad[0].ToggleCurve();
      if (GetState() == DropletState::kFull) {
	ad[1].ToggleCurve();
      }
    }
  }
}

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
  WriteString(Patch(),
	      GetScreenMin()+3,
	      11,
	      Font_6x8,
	      "A: " +
	      FloatToString(ad[0].GetAttack(), 2) +
	      "s");
  WriteString(Patch(),
	      GetScreenMin()+3,
	      21,
	      Font_6x8,
	      "D: " +
	      FloatToString(ad[0].GetDecay(), 2) +
	      "s");
  WriteString(Patch(),
	      GetScreenMin()+3,
	      31,
	      Font_6x8,
	      "C: " +
	      FloatToString(ad[0].GetCurve(), 2));
  if(GetState() == DropletState::kFull) {
    int mid = (GetScreenMax() - GetScreenMin())/2;
    WriteString(Patch(),
	        mid,
		11,
		Font_6x8,
		"A: " +
		FloatToString(ad[1].GetAttack(), 2) +
		"s");
    WriteString(Patch(),
		mid,
		21,
		Font_6x8,
		"D: " +
		FloatToString(ad[1].GetDecay(), 2) +
		"s");
    WriteString(Patch(),
		mid,
		31,
		Font_6x8,
		"C: " +
		FloatToString(ad[1].GetCurve(), 2));
  }

  if (ad[0].GetMenu()) {
    DrawSolidRect(Patch(), GetScreenMin(), 30, GetScreenMin()+1, 39, true);
  } else {
    DrawSolidRect(Patch(), GetScreenMin(), 10, GetScreenMin()+1, 19, true);
  }
  DrawSolidRect(Patch(), GetScreenMin(), 20, GetScreenMin()+1, 29, true);
  
  DrawName("AD");
}
