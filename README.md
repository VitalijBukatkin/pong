# Simple Pong game

## Uses
- C-11
- SDL2

## Require
- cc
- meson
- libsdl2-dev
- libsdl2-ttf-dev
- libsdl2-image-dev
- libsdl2-mixer-dev

## Building on Ubuntu
1. Execute `sudo apt install meson libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev`
2. Clone this repository and go to folder
3. Execute `meson build`
4. Application building: for build debian package, execute `ninja -C build package`
or simply build project, execute `ninja -C build`
5. You can install made package, execute `dpkg -i build/pong*.deb`

### For game you must have Gamepad with analog control