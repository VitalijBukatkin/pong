# Simple Pong Game

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

## Building on Windows
1. Install MSVC build tools
2. Install meson
3. Run `.\build-aux\windows_bundler.ps1`

## Building on Linux
1. Execute `sudo apt install meson libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev`
2. Clone this repository and go to folder
3. Execute `meson builddir`
4. Build project, execute `ninja -C builddir`
5. Run `cd builddir && ./pong`

## Building Flatpak package
1. Build and install: `cd build-aux && flatpak-builder --install build-dir com.github.witalijbukatkin.Pong.yml`
3. Run: `flatpak run com.github.witalijbukatkin.Pong`
