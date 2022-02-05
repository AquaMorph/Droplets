#include "sequencer_droplet.h"

SequencerDroplet::SequencerDroplet(DaisyPatch* m_patch,
				 DropletState m_state,
				 float sample_rate) :
  Droplet(m_patch,
	  m_state) {
  SetControls();
}

SequencerDroplet::~SequencerDroplet() {}

void SequencerDroplet::Control() {
  if(Patch()->gate_input[0].Trig()) {
    Step();
  }
  if(Patch()->gate_input[1].Trig()) {
    Reset();
  }

  for (size_t chn = GetChannelMin(); chn < GetChannelMax(); chn++) {
    sequence[chn+selected] = control[chn].Process();
  }
  
}

void SequencerDroplet::Process(AudioHandle::InputBuffer in,
			      AudioHandle::OutputBuffer out,
			      size_t size) {
  for(size_t i = 0; i < size; i++) {
    Patch()->seed.dac.WriteValue(DacHandle::Channel::ONE,
				 sequence[step] * 819.2f);
  }
}

void SequencerDroplet::Draw() {
  WriteString(Patch(), 0, 10, std::to_string(step));
  DrawName("Sequencer");
}

void SequencerDroplet::UpdateStateCallback() {}

void SequencerDroplet::SetControls() {
  control[0].Init(Patch()->controls[Patch()->CTRL_1],
	      0.0, 5.0f, Parameter::LINEAR);
  control[1].Init(Patch()->controls[Patch()->CTRL_2],
	      0.0, 5.0f, Parameter::LINEAR);
  control[2].Init(Patch()->controls[Patch()->CTRL_3],
	      0.0, 5.0f, Parameter::LINEAR);
  control[3].Init(Patch()->controls[Patch()->CTRL_4],
	      0.0, 5.0f, Parameter::LINEAR);
}

void SequencerDroplet::Step() {
  step = (step + 1) % MAX_SEQUENCE_LENGTH;
}

void SequencerDroplet::Reset() {
  step = 0;
}
