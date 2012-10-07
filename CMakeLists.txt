# vim: textwidth=0

cmake_minimum_required(VERSION 2.8)

project(ponic)

add_definitions(-O0 -g -rdynamic -Wall -Isrc/engine -D_DEBUG)

add_executable(bin/ponic
src/game/main_PC.cpp
src/game/MyApp.cpp
src/engine/Application_PC.cpp
src/engine/Graphics.h
src/engine/Graphics_PC.cpp
src/engine/ImageManager_COMMON.cpp
src/engine/ImageManager_PC.cpp
src/engine/ImageManager.h
src/engine/Input.h
src/engine/Log.h
src/engine/Log_PC.cpp
src/engine/misc/Singleton.h
src/engine/System.h
src/engine/System.cpp
src/engine/thirdparty/pugixml-1.2/pugiconfig.hpp
src/engine/thirdparty/pugixml-1.2/pugixml.cpp
src/engine/thirdparty/pugixml-1.2/pugixml.hpp
src/engine/thirdparty/tgaload/tgaload.c
src/engine/thirdparty/tgaload/tgaload.h
)

target_link_libraries(bin/ponic
#    -lglut -lGLESv2 -lGLU
    -lglut -lGLU
)
