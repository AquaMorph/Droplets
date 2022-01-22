#include "vca_droplet.h"

VCADroplet::VCADroplet(DaisyPatch* m_patch,
		       DropletState m_state) :
  Droplet(m_patch,
	  m_state) {
  SetControls();
}

VCADroplet::~VCADroplet() {}

void VCADroplet::Control() {}

void VCADroplet::Process(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size) {
  Patch()->ProcessAnalogControls();
  
  for (size_t i = 0; i < size; i++) {
    for (size_t chn = GetChannelMin(); chn < GetChannelMax(); chn++) {
      out[chn][i] = in[chn][i] * vca[chn].Process();
    }
  }
}

void VCADroplet::Draw() {
  int divider;
  switch (GetState()) {
  default:
  case DropletState::kFull:
    divider = (GetScreenMax()-GetScreenMin())/5;
    DrawFourDividedRectangles(Patch(),
			      divider,
			      GetScreenMin(),
			      GetScreenMax(),
			      0,
			      GetTitleHeight()*vca[0].Process(),
			      0,
			      GetTitleHeight()*vca[1].Process(),
			      0,
			      GetTitleHeight()*vca[2].Process(),
			      0,
			      GetTitleHeight()*vca[3].Process());
    break;
  case DropletState::kLeft:
    divider = (GetScreenMax()-GetScreenMin())/3;
    DrawTwoDividedRectangles(Patch(),
			     divider,
			     GetScreenMin(),
			     GetScreenMax(),
			     0,
			     GetTitleHeight()*vca[0].Process(),
			     0,
			     GetTitleHeight()*vca[1].Process());
    break;
  case DropletState::kRight:
    divider = (GetScreenMax()-GetScreenMin())/3;
    DrawTwoDividedRectangles(Patch(),
			     divider,
			     GetScreenMin(),
			     GetScreenMax(),
			     0,
			     GetTitleHeight()*vca[2].Process(),
			     0,
			     GetTitleHeight()*vca[3].Process());
    break;
  }
  DrawName("VCA");
}

void VCADroplet::UpdateStateCallback() {
  SetControls();
}

void VCADroplet::SetControls() {
  switch (GetState()) {
  default:
  case DropletState::kFull:
    vca[0].Init(Patch()->controls[Patch()->CTRL_1],
		0.0, 1.0f, Parameter::LINEAR);
    vca[1].Init(Patch()->controls[Patch()->CTRL_2],
		0.0, 1.0f, Parameter::LINEAR);
    vca[2].Init(Patch()->controls[Patch()->CTRL_3],
		0.0, 1.0f, Parameter::LINEAR);
    vca[3].Init(Patch()->controls[Patch()->CTRL_4],
		0.0, 1.0f, Parameter::LINEAR);
    break;
  case DropletState::kLeft:
    vca[0].Init(Patch()->controls[Patch()->CTRL_1],
		0.0, 1.0f, Parameter::LINEAR);
    vca[1].Init(Patch()->controls[Patch()->CTRL_2],
		0.0, 1.0f, Parameter::LINEAR);
    break;
  case DropletState::kRight:
    vca[2].Init(Patch()->controls[Patch()->CTRL_3],
		0.0, 1.0f, Parameter::LINEAR);
    vca[3].Init(Patch()->controls[Patch()->CTRL_4],
		0.0, 1.0f, Parameter::LINEAR);
    break;
  }
}
