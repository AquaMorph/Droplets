#include "template_droplet.h"

TemplateDroplet::TemplateDroplet(DaisyPatch* m_patch,
			   DropletState m_state) :
  Droplet(m_patch,
	  m_state) {
}

void TemplateDroplet::Control() {}

void TemplateDroplet::Process(AudioHandle::InputBuffer in,
			   AudioHandle::OutputBuffer out,
			   size_t size) {
}

void TemplateDroplet::Draw() {
  DrawName("Template");
}

void TemplateDroplet::UpdateStateCallback() {}
