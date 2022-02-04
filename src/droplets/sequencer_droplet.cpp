#include "sequencer_droplet.h"

SequencerDroplet::SequencerDroplet(DaisyPatch* m_patch,
				 DropletState m_state,
				 float sample_rate) :
  Droplet(m_patch,
	  m_state) {
}

SequencerDroplet::~SequencerDroplet() {}

void SequencerDroplet::Control() {
  if(Patch()->gate_input[0].Trig()) {
    Step();
  }
  if(Patch()->gate_input[1].Trig()) {
    Reset();
  }
}

void SequencerDroplet::Process(AudioHandle::InputBuffer in,
			      AudioHandle::OutputBuffer out,
			      size_t size) {
}

void SequencerDroplet::Draw() {
  WriteString(Patch(), 0, 10, std::to_string(step));
  DrawName("Sequencer");
}

void SequencerDroplet::UpdateStateCallback() {}

void SequencerDroplet::SetControls() {}

void SequencerDroplet::Step() {
  step = (step + 1) % MAX_SEQUENCE_LENGTH;
}

void SequencerDroplet::Reset() {
  step = 0;
}
