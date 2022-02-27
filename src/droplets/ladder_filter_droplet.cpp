#include "ladder_filter_droplet.h"

LadderFilterDroplet::LadderFilterDroplet(DaisyPatch* m_patch,
					 DropletState m_state,
					 float sample_rate) :
  Droplet(m_patch,
	  m_state) {

  for (int i = 0; i < 4; i++) {
    filter[i].Init(sample_rate);
  }

  SetControls();
}

LadderFilterDroplet::~LadderFilterDroplet() {}

void LadderFilterDroplet::Control() {}

void LadderFilterDroplet::Process(AudioHandle::InputBuffer in,
			   AudioHandle::OutputBuffer out,
			   size_t size) {
  freq = freq_ctrl.Process();
  res = res_ctrl.Process();
  
  for (size_t i = 0; i < size; i++) {
    for (size_t chn = GetChannelMin(); chn < GetChannelMax(); chn++) {
      filter[chn].SetFreq(freq);
      filter[chn].SetRes(res);
      out[chn][i] = filter[chn].Process(in[chn][i]) * (1.0f+res*4);
    }
  }
}

void LadderFilterDroplet::Draw() {
  int filter_cutoff_line = GetScreenMin()+(GetScreenWidth()*(freq/FILTER_MAX));
  DrawSolidRect(Patch(),
		GetScreenMin(),
		3,
		filter_cutoff_line,
		GetTitleHeight()-1,
		true);

  // Draw filter roll off
  Patch()->display.DrawLine(filter_cutoff_line+1, 5,
  			    filter_cutoff_line+1, GetTitleHeight()-1, true);

  // Draw Res
  res_points[0] = filter_cutoff_line-7*(res/RES_MAX);
  res_points[1] = filter_cutoff_line-3;
  res_points[2] = filter_cutoff_line-11*(res/RES_MAX);
  res_points[3] = filter_cutoff_line-2;
  res_points[4] = filter_cutoff_line-14*(res/RES_MAX);
  res_points[5] = filter_cutoff_line-1;

  for (int i = 0; i < 6; i++) {
    res_points[i] = std::max(GetScreenMin(), res_points[i]);
  }
  
  if (res > 0.6*RES_MAX) {
    Patch()->display.DrawLine(res_points[0], 0, res_points[1], 0, true);
  }
  if (res > 0.3*RES_MAX) {
    Patch()->display.DrawLine(res_points[2], 1, res_points[3], 1, true);
  }
  if (res > 0.1*RES_MAX) {
    Patch()->display.DrawLine(res_points[4], 2, res_points[5], 2, true);
  }
  
  DrawName("Ladder");
}

void LadderFilterDroplet::UpdateStateCallback() {}

void LadderFilterDroplet::SetControls() {
  AnalogControl filter_knob, res_knob;
  if (IsRight()) {
    filter_knob = Patch()->controls[Patch()->CTRL_3];
    res_knob = Patch()->controls[Patch()->CTRL_4];
  } else {
    filter_knob = Patch()->controls[Patch()->CTRL_1];
    res_knob = Patch()->controls[Patch()->CTRL_2];
  }
  freq_ctrl.Init(filter_knob, 5.0f, FILTER_MAX, Parameter::LOGARITHMIC);
  res_ctrl.Init(res_knob, 0.0f, RES_MAX, Parameter::LINEAR);
}
