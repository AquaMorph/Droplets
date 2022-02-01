#include "template_droplet.h"

TemplateDroplet::TemplateDroplet(DaisyPatch* m_patch,
				 DropletState m_state,
				 float sample_rate) :
  Droplet(m_patch,
	  m_state) {
}

TemplateDroplet::~TemplateDroplet() {}

void TemplateDroplet::Control() {}

void TemplateDroplet::Process(AudioHandle::InputBuffer in,
			      AudioHandle::OutputBuffer out,
			      size_t size) {
}

void TemplateDroplet::Draw() {
  DrawName("Template");
}

void TemplateDroplet::UpdateStateCallback() {}
