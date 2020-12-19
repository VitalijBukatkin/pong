project('pong', 'c')

dependencies = [
    meson.get_compiler('c').find_library('SDL2'),
    meson.get_compiler('c').find_library('SDL2_image'),
    meson.get_compiler('c').find_library('SDL2_mixer'),
    meson.get_compiler('c').find_library('SDL2_ttf'),
]

sources = files('src/pong.c', 'include/pong.h',
    'src/game.c', 'include/game.h',
    'include/diagnostics.h', 'src/diagnostics.c',
    'include/util/events.h', 'src/util/events.c',
    'include/util/loader.h', 'src/util/loader.c',
    'src/util/render.c', 'include/util/render.h',
    'src/util/common.c', 'include/util/common.h')

executable('pong', sources, dependencies: dependencies)
