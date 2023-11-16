#!/bin/sh

mkdir -p subprojects
meson wrap install glfw

if [ "$1" = "release" ]
then
  meson setup ./build/release --buildtype=release
  meson compile -C build/release
  cp -rf ./shaders ./build/release/shaders
  cp -f ./build/release/compile_commands.json .
else
  meson setup ./build/debug --buildtype=debug
  meson compile -C build/debug
  cp -rf ./shaders ./build/debug/shaders
  cp -f ./build/debug/compile_commands.json .
fi

