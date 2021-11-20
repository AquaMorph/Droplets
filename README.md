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
