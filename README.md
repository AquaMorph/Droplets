# Daisy Patch Template

A starting point for creating Daisy Patch Projects.

## Setup & Deploy
1. Create git repository
```sh
git clone git@github.com:AquaMorph/DaisyPatchTemplate.git [Project directory name]
git remote set-url origin [New git url]
git push
```
2. Build project
```sh
cd ./lib/daisySP && make && cd ../libDaisy && make && cd ../.. && make
```
3. Plug usb into Daisy. Enter bootloader mode by holding the BOOT button down, and then pressing the RESET button. Once you release the RESET button, you can also let go of the BOOT button
4. Write the binary to the Daisy
```sh
make && make program-dfu
```
