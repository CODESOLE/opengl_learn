#!/bin/sh

if [ "$1" = "release" ]
then
  printf "\nBuilding in release mode.\n"
  cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 && cmake --build build --config Release
else
  printf "\nBuilding in debug mode.\n"
  cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1 && cmake --build build --config Debug
fi

