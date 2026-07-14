# Repository Guide

## Scope

- This is one bare-metal C++ firmware target for the Electrosmith Daisy Patch. Application code is under `src/`; `lib/libDaisy` and `lib/daisySP` are recursive git submodules, not packages owned by this repository.
- Root CI only builds the firmware. Tests, formatters, and workflows found below `lib/` belong to the vendored submodules; there is no root application test or lint target.

## Build And Flash

- Initialize all nested dependencies after a non-recursive clone with `git submodule update --init --recursive`.
- The build requires the `arm-none-eabi-*` toolchain on `PATH`, or its binary directory passed as `GCC_PATH=...`. CI uses Arm GCC `9-2019-q4`.
- From a clean checkout, run `make lib && make`. `make lib` builds both submodule libraries; subsequent application-only changes normally need only `make`. Artifacts are `build/droplets.{elf,hex,bin}`.
- `make clean` removes only the root `build/`; it does not clean or rebuild either library.
- Do not use the README's `make deploy`: `APP_TYPE = BOOT_SRAM`, but that target invokes the incompatible OpenOCD `program` recipe and fails. After building, enter Daisy bootloader mode and run `make program-dfu` (requires `dfu-util`); it writes `build/droplets.bin` at `0x90040000`.

## Source Wiring

- `src/main.cpp` owns startup and dispatch: the foreground loop handles controls, OLED drawing, and non-audio outputs, while the Daisy audio callback calls each active droplet's `Process` method.
- Split mode runs left and right droplets against the same audio buffers. Use the `Droplet` state helpers and `GetChannelMin()`/`GetChannelMax()` plus screen bounds rather than hard-coded full-device ranges, or one side can overwrite the other.
- The root Makefile discovers only `src/*.cpp` and `src/*/*.cpp`. Sources nested more deeply are silently excluded. Object names are flattened into `build/`, so C++ source basenames must be unique across those directories.

## Adding A Droplet

- Run `./create-new-droplet.sh PascalCaseName`; the script only copies and substitutes the template and does not register the result.
- Complete all registration points: add a `MenuState` in `src/menu_item.h`, append its visible item in `Menu::Menu` in `src/menu.cpp`, include its header in `src/main.h`, and add construction in `GetDroplet` in `src/main.cpp`.
- Implement all three `DropletState` layouts. `Droplet::UpdateState` recalculates channel/display bounds, then calls `SetControls()` and `UpdateStateCallback()` when switching between full and split modes.
