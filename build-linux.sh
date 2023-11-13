#!/bin/sh

if [ "$1" = "release" ]
then
  conan profile detect --force
  conan install . --build=missing --settings=build_type=Release
  cmake --preset conan-default
  cmake --build build --config Release
else
  conan profile detect --force
  conan install . --build=missing --settings=build_type=Debug
  cmake --preset conan-default
  cmake --build build --config Debug
fi

