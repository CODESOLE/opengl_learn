@echo off

mkdir subprojects
meson wrap install glfw

setlocal EnableDelayedExpansion
IF "%1"=="release" (
  meson setup .\build\release --buildtype=release
  meson compile -C build\release
  Xcopy .\shaders .\build\release\shaders /S/E/C/I/Y/D
  Xcopy .\build\debug\compile_commands.json . /Y/D
) ELSE (
  meson setup .\build\debug --buildtype=debug
  meson compile -C build\debug
  Xcopy .\shaders .\build\debug\shaders /S/E/C/I/Y/D
  Xcopy .\build\debug\compile_commands.json . /Y/D
)
