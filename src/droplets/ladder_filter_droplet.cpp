#include "ladder_filter_droplet.h"

LadderFilterDroplet::LadderFilterDroplet(DaisyPatch* m_patch,
					 DropletState m_state,
					 float sample_rate) :
  Droplet(m_patch,
	  m_state) {
  filter.Init(sample_rate);

  SetControls();
}

void LadderFilterDroplet::Control() {}

void LadderFilterDroplet::Process(AudioHandle::InputBuffer in,
			   AudioHandle::OutputBuffer out,
			   size_t size) {
  freq = freq_ctrl.Process();
  res = res_ctrl.Process();
  filter.SetFreq(freq);
  filter.SetRes(res);
  for (size_t i = 0; i < size; i++) {
    for (size_t chn = GetChannelMin(); chn < GetChannelMax(); chn++) {
      out[chn][i] = filter.Process(in[chn][i]) * (1.0f+res*4);
    }
  }
}

void LadderFilterDroplet::Draw() {
  DrawName("Ladder");
}

void LadderFilterDroplet::UpdateStateCallback() {}

void LadderFilterDroplet::SetControls() {
  AnalogControl filter_knob, res_knob;
  if (GetState() == DropletState::kRight) {
    filter_knob = Patch()->controls[Patch()->CTRL_3];
    res_knob = Patch()->controls[Patch()->CTRL_4];
  } else {
    filter_knob = Patch()->controls[Patch()->CTRL_1];
    res_knob = Patch()->controls[Patch()->CTRL_2];
  }
  freq_ctrl.Init(filter_knob, 5.0f, 10000.0f, Parameter::LOGARITHMIC);
  res_ctrl.Init(res_knob, 0.0f, 0.95f, Parameter::LINEAR);
}
