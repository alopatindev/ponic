# vim: textwidth=0

set(APP_NAME ponic)

cmake_minimum_required(VERSION 2.8)

project(${APP_NAME})

find_package(PkgConfig)
pkg_check_modules(FREETYPE2 freetype2)

link_directories(
    ${FREETYPE2_LIBRARY_DIRS}
)
include_directories(
    ${FREETYPE2_INCLUDE_DIRS}
    ../../src
    ../../src/engine
    ../../src/engine/thirdparty/glm
)

add_definitions(
    -fno-exceptions -Wall -DPUGIXML_NO_EXCEPTIONS
)

add_executable(bin/${APP_NAME}
../../src/game/Background3D.cpp
../../src/game/Effects.cpp
../../src/game/MyApp.cpp
../../src/game/Player.cpp
../../src/game/Scene.cpp
../../src/game/GameObjects/Platform.cpp
../../src/engine/Camera.cpp
../../src/engine/drawables/Drawable3D.cpp
../../src/engine/drawables/Drawable3DGrid.cpp
../../src/engine/drawables/Drawable3DImage.cpp
../../src/engine/GridManager.cpp
../../src/engine/misc/Utils.cpp
../../src/engine/platforms/common/ImageManager.cpp
../../src/engine/platforms/common/Graphics.cpp
../../src/engine/platforms/linux/Application.cpp
../../src/engine/platforms/linux/FontManager.cpp
../../src/engine/platforms/linux/Graphics.cpp
../../src/engine/platforms/linux/ImageManager.cpp
../../src/engine/platforms/linux/Input.cpp
../../src/engine/platforms/linux/Log.cpp
../../src/engine/platforms/linux/main.cpp
../../src/engine/System.cpp
../../src/engine/thirdparty/pugixml-1.2/pugixml.cpp
../../src/engine/thirdparty/tgaload/tgaload.c
)

target_link_libraries(bin/${APP_NAME}
#    -lglut -lGLESv2 -lGLU
    -lglut -lGLU -lGLEW
    ${FREETYPE2_LIBRARIES}
)
