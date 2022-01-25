#include "droplet.h"

Droplet::Droplet(DaisyPatch* m_patch, DropletState m_state) {
  patch = m_patch;
  UpdateState(m_state);
}

DaisyPatch* Droplet::Patch() {
  return patch;
}

DropletState* Droplet::State() {
  return &state;
}

DropletState Droplet::GetState() {
  return state;
}

int Droplet::GetTitleHeight() {
  return kTitleHeight;
}

int Droplet::GetScreenMin() {
  return screen_min;
}

int Droplet::GetScreenMax() {
  return screen_max;
}

size_t Droplet::GetChannelMin() {
  return chn_min;
}

size_t Droplet::GetChannelMax() {
  return chn_max;
}

void Droplet::DrawName(std::string name) {
  WriteCenteredString(patch, (screen_min + screen_max) / 2, 0,
		      Font_6x8, name);
}

void Droplet::UpdateState(DropletState m_state) {
  state = m_state;
  chn_min = 0;
  chn_max = 4;
  screen_min = 0;
  screen_max = SSD1309_WIDTH;
  if (state == DropletState::kLeft) {
    chn_max = 2;
    screen_max = SSD1309_WIDTH / 2;
  } else if (state == DropletState::kRight) {
    chn_min = 2;
    screen_min = SSD1309_WIDTH / 2;
  }
  SetControls();
  UpdateStateCallback();
}

void Droplet::AnimationInc() {
  if (count == animation_rate) {
    animation_count++;
    count = 0;
  }
  count++;
}

void Droplet::SetAnimationRate(int rate) {
  animation_rate = rate;
}

int Droplet::GetAnimationCount() {
  return animation_count;
}

bool Droplet::NeedUpdate() {
  return count % animation_rate == 0;
}
