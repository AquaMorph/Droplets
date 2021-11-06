#pragma once

#ifndef CASCADE_MAIN_H_
#define CASCADE_MAIN_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include <string>

#include "util.h"
#include "menu.h"
#include "droplets/droplet.h"
#include "droplets/droplet_manager.h"
#include "droplets/lfo_droplet.h"
#include "droplets/mixer_droplet.h"
#include "droplets/noise_droplet.h"
#include "droplets/vca_droplet.h"
#include "droplets/vco_droplet.h"

DaisyPatch patch;
DropletManager* manager = new DropletManager();
Menu* selected_menu;
Menu* left_menu = new Menu(&patch, DropletState::kLeft, manager);
Menu* right_menu = new Menu(&patch, DropletState::kRight, manager);
Droplet* droplet_left;
Droplet* droplet_right;
float sample_rate;

/*
 * Processes user controls and inputs.
 */
void ProcessControls();

/*
 * Processes information to be displayed on the screen. 
 */
void ProcessOled();

/*
 * Processes patch outputs.
 */
void ProcessOutputs();

/*
 * Processes audio input and outputs with a faster and higher priority control
 * loop.
 *
 * @param in the audio inputs for the patch
 * @param out the audio outputs for the patch
 * @param size the number of inputs and outputs
 */
static void AudioThrough(AudioHandle::InputBuffer in,
			 AudioHandle::OutputBuffer out,
			 size_t size);

/*
 * Initializes a new audio processing droplet based on menu state.
 *
 * @param state new droplet state
 * @return droplet
 */
Droplet* GetDroplet(DropletState state);

#endif // CASCADE_MAIN_H_
