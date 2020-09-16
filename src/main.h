#include "daisysp.h"
#include "daisy_patch.h"

#include <string>

#include "util.h"
#include "menu.h"
#include "droplets/droplet.h"
#include "droplets/noise_droplet.h"
#include "droplets/vco_droplet.h"

void ProcessControls();
void ProcessOled();
void ProcessOutputs();
static void AudioThrough(float **, float **, size_t);
Droplet* GetDroplet();
