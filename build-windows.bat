@echo off

setlocal EnableDelayedExpansion

conan profile detect --force
REM conan install . -s &:build_type=Debug -s build_type=Release --build=missing
conan install . --build=missing
cmake --preset conan-default
cmake --build build --config Release
