#include "ad_droplet.h"

void AD::Init(DaisyPatch* m_patch,
	      float sample_rate,
	      DropletState* m_state) {
    patch = m_patch;
    state = m_state;
    env.Init(sample_rate);
    env.SetMax(1.0f);
    env.SetMin(0.0f);
    env.SetCurve(0.0f);

    SetControls();
  }

void AD::Process(DacHandle::Channel chn,
		 DaisyPatch::GateInput gate) {
  if(patch->gate_input[gate].Trig()) {
    env.Trigger();
  }
  if (*state == DropletState::kFull) {
    attack = attack_param.Process();
    decay = decay_param.Process();
    curve = curve_param.Process();
    amp = amp_param.Process();
  } else if (curve_menu) {
    curve = curve_param.Process();
    amp = amp_param.Process();
  } else {
    attack = attack_param.Process();
    decay = decay_param.Process();
  }
  
  env.SetTime(ADENV_SEG_ATTACK, attack);
  env.SetTime(ADENV_SEG_DECAY, decay);
  env.SetCurve(curve);
  
  sig = env.Process();
  patch->seed.dac.WriteValue(chn,
  sig * amp * 4095.0f);
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

float AD::GetAmp() {
  return amp;
}

bool AD::GetMenu() {
  return curve_menu;
}

void AD::ToggleCurve() {
  curve_menu = !curve_menu;
}

void AD::SetControls() {
  AnalogControl attack_knob, decay_knob, curve_knob, amp_knob;

  switch (*state) {
  default:
  case DropletState::kFull:
    attack_knob = patch->controls[patch->CTRL_1];
    decay_knob = patch->controls[patch->CTRL_2];
    curve_knob = patch->controls[patch->CTRL_3];
    amp_knob = patch->controls[patch->CTRL_4];
    break;
  case DropletState::kLeft:
    attack_knob = patch->controls[patch->CTRL_1];
    decay_knob = patch->controls[patch->CTRL_2];
    curve_knob = patch->controls[patch->CTRL_1];
    amp_knob = patch->controls[patch->CTRL_2];
    break;
  case DropletState::kRight:
    attack_knob = patch->controls[patch->CTRL_3];
    decay_knob = patch->controls[patch->CTRL_4];
    curve_knob = patch->controls[patch->CTRL_3];
    amp_knob = patch->controls[patch->CTRL_4];
    break;
  }
  
  attack_param.Init(attack_knob, .01f, 3.0f, Parameter::EXPONENTIAL);
  decay_param.Init(decay_knob, .01f, 3.0f, Parameter::EXPONENTIAL);
  curve_param.Init(curve_knob, -10.f, 10.0f, Parameter::LINEAR);
  amp_param.Init(amp_knob, 0.0f, 1.0f, Parameter::LINEAR);
}

ADDroplet::ADDroplet(DaisyPatch* m_patch,
		       DropletState m_state,
		       float m_sample_rate) :
  Droplet(m_patch,
	  m_state) {
  sample_rate = m_sample_rate;
  SetAnimationRate(10);
  ad[0].Init(Patch(),
	     sample_rate,
	     &m_state);
  if (m_state == DropletState::kFull) {
    ad[1].Init(Patch(),
	       sample_rate,
	       &m_state);
  }

  title_graph = new Graph(GetScreenMax()-GetScreenMin(),
			  GetTitleHeight());
}

ADDroplet::~ADDroplet() {
  delete title_graph;
}

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
      out[chn][i] = in[chn][i] * ad[env_sel].GetSignal() *
	ad[env_sel].GetAmp();
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
  WriteString(Patch(),
	      GetScreenMin()+3,
	      41,
	      Font_6x8,
	      "Amp: " +
	      FloatToString(ad[0].GetAmp(), 2));

  if (GetState() != DropletState::kFull) {
    if (ad[0].GetMenu()) {
      DrawSolidRect(Patch(), GetScreenMin(), 30, GetScreenMin()+1, 49, true);
    } else {
      DrawSolidRect(Patch(), GetScreenMin(), 10, GetScreenMin()+1, 29, true);
    }
  }

  if(NeedUpdate()) {
    title_graph->Update();
  }
  title_graph->SetPixelPercentage(ad[0].GetSignal());
  title_graph->Draw(Patch(), GetScreenMin(), 0);
  
  DrawName("AD");
  AnimationInc();
}

void ADDroplet::UpdateStateCallback() {
  ad[0].Init(Patch(),
	     sample_rate,
	     State());
  if (GetState() == DropletState::kFull) {
    ad[1].Init(Patch(),
	       sample_rate,
	       State());
  }
  title_graph = new Graph(GetScreenMax()-GetScreenMin(),
			  GetTitleHeight());
}
