@echo off

setlocal EnableDelayedExpansion
IF "%1"=="release" (
  conan profile detect --force
  conan install . --build=missing --settings=build_type=Release
  cmake --preset conan-default
  cmake --build build --config Release
) ELSE (
  conan profile detect --force
  conan install . --build=missing --settings=build_type=Debug
  cmake --preset conan-default
  cmake --build build --config Debug
)
