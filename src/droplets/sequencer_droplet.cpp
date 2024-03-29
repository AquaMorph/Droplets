#include "sequencer_droplet.h"

SequencerDroplet::SequencerDroplet(DaisyPatch* m_patch,
				 DropletState m_state,
				 float sample_rate) :
  Droplet(m_patch,
	  m_state) {
  SetAnimationRate(20);
  CreateTitleGraph();
  SetDimensions();
  SetControls();
  SetInMenu();
}

SequencerDroplet::~SequencerDroplet() {
  delete title_graph;
}

void SequencerDroplet::Control() {
  Patch()->ProcessAnalogControls();
  Patch()->encoder.Debounce();
  AdjustSelected(Patch()->encoder.Increment());
}

void SequencerDroplet::Process(AudioHandle::InputBuffer in,
			      AudioHandle::OutputBuffer out,
			      size_t size) {
  // Step input for full and left droplets
  if(!IsRight() && Patch()->gate_input[0].Trig()) {
    Step();
  }

  // Step for right droplet and reset for full
  if(!IsLeft() && Patch()->gate_input[1].Trig()) {
    if (IsFull()) {
      Reset();
    } else {
      Step();
    }
  }

  // Limit control update rate to reduce noise
  if (control_rate_count == CONTROL_RATE_LIMIT) {
    for (size_t chn = GetChannelMin(); chn < GetChannelMax(); chn++) {
      // Check for control being moved
      if (std::abs(control[chn].Process()
		   -last_control_value[chn]) > CONTROL_DEADZONE) {
	int right_offset = IsRight() ? -2 : 0;
	if (!InMenu() && (int) chn+selected*num_columns+right_offset < sequence_length) {
	  sequence[chn+selected*num_columns+right_offset] = control[chn].Process();
	} else {
	  // Set sequence length
	  if (chn == GetChannelMin()) {
	    sequence_length = std::max(1.0f,control[chn].Process() /
				       4.85f*MAX_SEQUENCE_LENGTH);
	    SetDimensions();
	    SetInMenu();
	  }
	  // Set clock divider
	  if (chn == GetChannelMin()+1) {
	    divider = std::max(1.0f,control[chn].Process() /
				       4.85f*MAX_CLOCK_DIVIDE);
	  }
	}
      }
      last_control_value[chn] = control[chn].Process();
    }
    control_rate_count = 0;
  }
  control_rate_count++;

  // VC output of sequencer
  for(size_t i = 0; i < size; i++) {
    if (!IsRight()) {
      Patch()->seed.dac.WriteValue(DacHandle::Channel::ONE,
				   sequence[step] * 819.2f);
    }
    if (!IsRight()) {
      Patch()->seed.dac.WriteValue(DacHandle::Channel::TWO,
				   sequence[step] * 819.2f);
    }
  }
}

void SequencerDroplet::Draw() {
  int left_padding = 4+GetScreenMin();
  int offset = step / (num_columns*NUM_ROWS);
  
  // Active Input
  if (!InMenu()) {
    offset = selected / NUM_ROWS;
    DrawSolidRect(Patch(),
		  GetScreenMin(),
		  8+selected%NUM_ROWS*8,
		  GetScreenMin()+2,
		  15+selected%NUM_ROWS*8, true);
  }
  offset *= num_columns*NUM_ROWS;

  // Notes
  for (int i = 0; i < num_columns*NUM_ROWS && i+offset < sequence_length; i++) {
    WriteString(Patch(),
		GetScreenWidth()/num_columns*(i%num_columns)+left_padding,
		8+(std::floor(i/num_columns)*8),
		FloatToString(sequence[i+offset], 2),
		i+offset!=step);
  }

  // Draw info bar
  DrawSolidRect(Patch(),GetScreenMin(),56,GetScreenMax(),63, InMenu());
  length_text = std::to_string(step+1);
  if (sequence_length >= 10) {
    length_text.insert(length_text.begin(), 2 - length_text.length(), '0');
  }
  length_text.append("/"+std::to_string(sequence_length));
  WriteString(Patch(),
	      2+GetScreenMin(),
	      56,
	      length_text,
	      !InMenu());
  WriteString(Patch(),
	      36+GetScreenMin(),
	      56,
	      std::to_string(divider),
	      !InMenu());

  if(NeedUpdate()) {
    title_graph->Update();
  }
  title_graph->SetPixelPercentage(sequence[step]/5.0f);
  title_graph->Draw(Patch(), GetScreenMin(), 0);
  DrawName("Sequencer");
}

void SequencerDroplet::UpdateStateCallback() {
  SetDimensions();
  SetInMenu();
  delete title_graph;
  CreateTitleGraph();
}

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
  divider_count = (divider_count + 1) % divider;
  if (divider_count == 0) {
    step = (step + 1) % sequence_length;
  }
}

void SequencerDroplet::Reset() {
  step = 0;
}

void SequencerDroplet::SetDimensions() {
  if (!IsFull()) {
    num_columns = 2;
  } else {
    num_columns = 4;
  }
  num_rows = std::ceil((float)sequence_length/num_columns);
}

void SequencerDroplet::AdjustSelected(int adj) {
  selected = (num_rows+selected+adj+1) % (num_rows+1);
}

bool SequencerDroplet::InMenu() {
  return selected >= num_rows;
}

void SequencerDroplet::SetInMenu() {
  selected = 0;
  AdjustSelected(-1);
}

void SequencerDroplet::CreateTitleGraph() {
  title_graph = new Graph(GetScreenMax()-GetScreenMin(),
			  GetTitleHeight());
}
