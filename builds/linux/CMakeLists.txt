# vim: textwidth=0

cmake_minimum_required(VERSION 2.8)

project(ponic)

find_package(PkgConfig)
pkg_check_modules(FREETYPE2 freetype2)

link_directories(
    ${FREETYPE2_LIBRARY_DIRS}
)
include_directories(
    ${FREETYPE2_INCLUDE_DIRS}
    ../../src/engine
)

add_definitions(-O0 -g -rdynamic -Wall -D_DEBUG -DPUGIXML_NO_EXCEPTIONS)

add_executable(bin/ponic
../../src/game/Effects.cpp
../../src/game/Effects.h
../../src/game/MyApp.cpp
../../src/engine/Assert.h
../../src/engine/Application.h
../../src/engine/platforms/linux/Application.cpp
../../src/engine/platforms/linux/FontManager.cpp
../../src/engine/FontManager.h
../../src/engine/Graphics.h
../../src/engine/ImageManager.h
../../src/engine/Input.h
../../src/engine/Log.h
../../src/engine/misc/Singleton.h
../../src/engine/platforms/common/ImageManager.cpp
../../src/engine/platforms/linux/Graphics.cpp
../../src/engine/platforms/linux/ImageManager.cpp
../../src/engine/platforms/linux/Log.cpp
../../src/engine/platforms/linux/main.cpp
../../src/engine/System.h
../../src/engine/System.cpp
../../src/engine/Utils.h
../../src/engine/Utils.cpp
../../src/engine/thirdparty/freetype-gl/freetype-gl.h
../../src/engine/thirdparty/freetype-gl/opengl.h
../../src/engine/thirdparty/freetype-gl/texture-atlas.c
../../src/engine/thirdparty/freetype-gl/texture-atlas.h
../../src/engine/thirdparty/freetype-gl/texture-font.c
../../src/engine/thirdparty/freetype-gl/texture-font.h
../../src/engine/thirdparty/freetype-gl/vec234.h
../../src/engine/thirdparty/freetype-gl/vector.c
../../src/engine/thirdparty/freetype-gl/vector.h
../../src/engine/thirdparty/freetype-gl/vertex-attribute.c
../../src/engine/thirdparty/freetype-gl/vertex-attribute.h
../../src/engine/thirdparty/freetype-gl/vertex-buffer.c
../../src/engine/thirdparty/freetype-gl/vertex-buffer.h
../../src/engine/thirdparty/pugixml-1.2/pugiconfig.hpp
../../src/engine/thirdparty/pugixml-1.2/pugixml.cpp
../../src/engine/thirdparty/pugixml-1.2/pugixml.hpp
../../src/engine/thirdparty/tgaload/tgaload.c
../../src/engine/thirdparty/tgaload/tgaload.h
)

target_link_libraries(bin/ponic
#    -lglut -lGLESv2 -lGLU
    -lglut -lGLU -lGLEW
    ${FREETYPE2_LIBRARIES}
)
