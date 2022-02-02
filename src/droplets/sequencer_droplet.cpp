#include "sequencer_droplet.h"

SequencerDroplet::SequencerDroplet(DaisyPatch* m_patch,
				 DropletState m_state,
				 float sample_rate) :
  Droplet(m_patch,
	  m_state) {
}

SequencerDroplet::~SequencerDroplet() {}

void SequencerDroplet::Control() {}

void SequencerDroplet::Process(AudioHandle::InputBuffer in,
			      AudioHandle::OutputBuffer out,
			      size_t size) {
}

void SequencerDroplet::Draw() {
  DrawName("Sequencer");
}

void SequencerDroplet::UpdateStateCallback() {}

void SequencerDroplet::SetControls() {}
