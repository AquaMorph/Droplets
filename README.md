# Droplets

Custom firmware for the Electrosmith Daisy Patch.

## Setup & Build
1. Create git repository
```sh
git clone --recurse-submodules git@github.com:AquaMorph/Droplets.git
```
2. Build project
```sh
make lib && make
```

## Deploy
1. Plug usb into Daisy. Enter bootloader mode by holding the BOOT button down, and then pressing the RESET button. Once you release the RESET button, you can also let go of the BOOT button
2. Write the binary to the Daisy
```sh
make deploy
```

## Creating Droplets

The Droplets firmware is based around writing modular code blocks called droplets. A droplet needs to support three states (full, left, right). Droplets should have an animated title bar that ideally interacts with the current state of the droplet.

### Hardware Allocation

#### Full Mode

CTRL [1-4]
GATE IN [1-2]
GATE OUT 1
AUDIO IN [1-4]
AUDIO OUT [1-4]
MIDI IN
MIDI OUT
CV OUT [1-2]

#### Left Mode

CTRL [1-2]
GATE IN 1
GATE OUT 1
AUDIO IN [1-2]
AUDIO OUT [1-2]
MIDI IN
MIDI OUT
CV OUT 1

#### Right Mode

CTRL [3-4]
GATE IN 2
AUDIO IN [3-4]
AUDIO OUT [3-4]
CV OUT 2

### Setting Up Code

1. Create new c++ program and header file from the Droplet template.

```sh
create-new-droplet.sh [Droplet Name]
```

2. Add a MenuState enum for the new droplet in the `menu_item.h` with the format of k[Droplet Name]. 

3. Add menu to the `menu.cpp` by creating a new AddItemEnd to the list with the MenuState and droplet name.

4. Include the droplet header in the `main.h` file.

5. In the GetDroplet function in `main.cpp` add a case for the new droplet to return a constructor.
