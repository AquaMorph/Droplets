#pragma once

#ifndef CASCADE_MAIN_H_
#define CASCADE_MAIN_H_

#include "daisysp.h"
#include "daisy_patch.h"

#include <string>

#include "util.h"
#include "menu.h"
#include "droplets/droplet.h"
#include "droplets/noise_droplet.h"
#include "droplets/vco_droplet.h"

DaisyPatch patch;
bool split = false;
Menu left_menu(&patch, "Right", &split);
Menu right_menu(&patch, "Left", &split);
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
static void AudioThrough(float** in,
			 float** out,
			 size_t size);

/*
 * Initializes a new audio processing droplet based on menu state.
 *
 * @param state new droplet state
 * @return droplet
 */
Droplet* GetDroplet(DropletState state);

#endif // CASCADE_MAIN_H_
