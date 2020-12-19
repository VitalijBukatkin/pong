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
- flatpak-builder (for build flatpak)

## Controls
- LEFT - W, S / LEFT STICK
- RIGHT - UP, DOWN / RIGHT STICK

## Building on Ubuntu
1. Execute `sudo apt install meson libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev fakeroot`
2. Clone this repository and go to folder
3. Execute `meson builddir`
4. Build project, execute `ninja -C builddir`

## Make flatpak
1. `cd build-aux`
2. `flatpak-builder --install build-dir com.github.witalijbukatkin.Pong.yaml`
3. `flatpak run com.github.witalijbukatkin.Pong`