#include "vca_droplet.h"

VCADroplet::VCADroplet(DaisyPatch* m_patch,
		       DropletState m_state) :
  Droplet(m_patch,
	  m_state) {
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
    DrawSolidRect(Patch(),
		  GetScreenMin(),
		  0,
		  divider,
		  GetTitleHeight()*vca[0].Process(),
		  true);
    DrawSolidRect(Patch(),
		  GetScreenMin()+divider,
		  0,
		  GetScreenMin()+divider*2,
		  GetTitleHeight()*vca[1].Process(),
		  true);
    DrawSolidRect(Patch(),
		  GetScreenMin()+divider*3,
		  0,
		  GetScreenMin()+divider*4,
		  GetTitleHeight()*vca[2].Process(),
		  true);
    DrawSolidRect(Patch(),
		  GetScreenMin()+divider*4,
		  0,
		  GetScreenMax(),
		  GetTitleHeight()*vca[3].Process(),
		  true);
    break;
  case DropletState::kLeft:
    divider = (GetScreenMax()-GetScreenMin())/3;
    DrawSolidRect(Patch(),
		  GetScreenMin(),
		  0,
		  GetScreenMin()+divider,
		  GetTitleHeight()*vca[0].Process(),
		  true);
    DrawSolidRect(Patch(),
		  GetScreenMax()-divider,
		  0,
		  GetScreenMax(),
		  GetTitleHeight()*vca[1].Process(),
		  true);
    break;
  case DropletState::kRight:
    divider = (GetScreenMax()-GetScreenMin())/3;
    DrawSolidRect(Patch(),
		  GetScreenMin(),
		  0,
		  GetScreenMin()+divider,
		  GetTitleHeight()*vca[2].Process(),
		  true);
    DrawSolidRect(Patch(),
		  GetScreenMax()-divider,
		  0,
		  GetScreenMax(),
		  GetTitleHeight()*vca[3].Process(),
		  true);
    break;
  }
  DrawName("VCA");
}

void VCADroplet::UpdateStateCallback() {}
