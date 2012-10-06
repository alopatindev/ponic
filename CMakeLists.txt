# vim: textwidth=0

cmake_minimum_required(VERSION 2.8)

project(ponic)

add_definitions(-O0 -g -rdynamic -Wall -Isrc/Engine -D_DEBUG)

add_executable(bin/ponic
src/Game/main_PC.cpp
src/Game/MyApp.cpp
src/Engine/Application_PC.cpp
src/Engine/Graphics.h
src/Engine/Graphics_PC.cpp
src/Engine/ImageManager_COMMON.cpp
src/Engine/ImageManager_PC.cpp
src/Engine/ImageManager.h
src/Engine/Input.h
src/Engine/Log.h
src/Engine/Log_PC.cpp
src/Engine/misc/Singleton.h
src/Engine/System.h
src/Engine/System.cpp
src/Engine/thirdparty/pugixml-1.2/pugiconfig.hpp
src/Engine/thirdparty/pugixml-1.2/pugixml.cpp
src/Engine/thirdparty/pugixml-1.2/pugixml.hpp
src/Engine/thirdparty/tgaload/tgaload.c
src/Engine/thirdparty/tgaload/tgaload.h
)

target_link_libraries(bin/ponic
#    -lglut -lGLESv2 -lGLU
    -lglut -lGLU
)
