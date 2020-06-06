cmake_minimum_required(VERSION 3.16)
project(Pong C)

set(CMAKE_C_STANDARD 11)

add_executable(pong src/pong.c include/pong.h
        src/game.c include/game.h
        include/diagnostics.h src/diagnostics.c
        include/util/events.h src/util/events.c
        include/util/loader.h src/util/loader.c
        src/util/render.c include/util/render.h
        include/util/common.h src/util/common.c)

target_link_libraries(pong SDL2 SDL2_ttf SDL2_image SDL2_mixer)
