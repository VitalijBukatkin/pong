project('pong', 'c')

dependencies = [
    dependency('sdl2'),
    dependency('SDL2_ttf'),
    dependency('SDL2_mixer'),
    dependency('SDL2_image'),
]

if host_machine.system() == 'windows'
    dependencies += dependency('sdl2main')
endif

sources = [
    'src/pong.c',
    'src/game.c',
    'src/support.c',
]

executable('pong', 
    sources, 
    win_subsystem: 'windows', 
    dependencies: dependencies)
