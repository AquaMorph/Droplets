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
      out[chn][i] = filter.Process(in[chn][i]);
    }
  }
}

void LadderFilterDroplet::Draw() {
  DrawName("Ladder");
}

void LadderFilterDroplet::UpdateStateCallback() {}

void LadderFilterDroplet::SetControls() {
  if (GetState() == DropletState::kRight) {
    freq_ctrl.Init(Patch()->controls[Patch()->CTRL_3],
		   0.0, 10000.0f, Parameter::LINEAR);
    res_ctrl.Init(Patch()->controls[Patch()->CTRL_4],
		  0.0, 0.75f, Parameter::LINEAR);
  } else {
    freq_ctrl.Init(Patch()->controls[Patch()->CTRL_1],
		   0.0, 10000.0f, Parameter::LINEAR);
    res_ctrl.Init(Patch()->controls[Patch()->CTRL_2],
		  0.0, 0.75f, Parameter::LINEAR);
  }
}
