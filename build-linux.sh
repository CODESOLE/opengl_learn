#!/bin/sh

if [ "$1" = "release" ]
then
  conan profile detect --force
  conan install . --build=missing --settings=build_type=Release
  cmake --preset conan-release
  cmake --build build/Release --config Release
else
  conan profile detect --force
  conan install . --build=missing --settings=build_type=Debug
  cmake --preset conan-debug
  cmake --build build/Debug --config Debug
fi

