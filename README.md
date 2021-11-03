# OpenGL Learn
[![ci](https://github.com/codesole/opengl_learn/actions/workflows/ci.yml/badge.svg)](https://github.com/codesole/opengl_learn/actions?query=workflow%3Aci)
[![Build Status](https://travis-ci.com/CODESOLE/opengl_learn.svg?branch=main)](https://travis-ci.com/CODESOLE/opengl_learn)
[![CodeQL](https://github.com/CODESOLE/opengl_learn/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/CODESOLE/opengl_learn/actions/workflows/codeql-analysis.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/codesole/opengl_learn/badge)](https://www.codefactor.io/repository/github/codesole/opengl_learn)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/5d023f93e2744e559111e6bf8953d557)](https://www.codacy.com/gh/CODESOLE/opengl_learn/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=CODESOLE/opengl_learn&amp;utm_campaign=Badge_Grade)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/CODESOLE/opengl_learn.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/CODESOLE/opengl_learn/context:cpp)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/CODESOLE/opengl_learn.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/CODESOLE/opengl_learn/alerts/)
[![codecov](https://codecov.io/gh/CODESOLE/opengl_learn/branch/main/graph/badge.svg?token=P4D64PE9Z4)](https://codecov.io/gh/CODESOLE/opengl_learn)
[![Coverity Scan](https://scan.coverity.com/projects/23555/badge.svg)](https://scan.coverity.com/projects/noobwebengine)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

OpenGL Learn.

# Dependencies
 - [CMake](https://cmake.org/download/)
 - [MinGW-W64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)  ( If you want to build with make along with gcc )
 - [Ninja](https://github.com/ninja-build/ninja/releases)  ( If you want to build with ninja along with gcc which is default )
 - [Visual Studio](https://visualstudio.microsoft.com/downloads/)  ( If you want to build with MSBuild (Windows Native build tools) )
 - [Git](https://git-scm.com/downloads) or [Github Desktop](https://desktop.github.com/)

 **Make sure these are installed and on your PATH.**

```
git clone https://https://github.com/CODESOLE/opengl_learn.git
```
# Linux Specific Dependencies
For Ubuntu you can install dependencies with this command : ```sudo apt update && sudo apt upgrade && sudo apt install libglfw3 libglfw3-dev libxcursor-dev libxinerama-dev libxrandr-dev build-essential cmake libxi-dev ninja-build pkg-config libx11-dev```. Install them according to your distribution package name.

# Build Instructions For WINDOWS
Run ```build-windows.bat <target-build-system> <Compiler-Collection>``` target build system can be ninja, make or msbuild. Compiler-Collection can be gcc or clang If your target-build-system is make or ninja other than msbuild. For example:

```build-windows.bat ninja```         -> it will choose gcc with ninja

```build-windows.bat msbuild```       -> it will choose MSVC with MSBuild

```build-windows.bat make```          -> it will choose gcc with make

```build-windows.bat ninja gcc```     -> it will choose gcc with ninja

```build-windows.bat make gcc```      -> it will choose gcc with make

```build-windows.bat ninja clang```   -> it will choose clang with ninja

```build-windows.bat make clang```    -> it will choose clang with make

If you are not specify the build-target, it will choose ninja as default.


# Build Instructions For LINUX
Run ```build-linux.sh <target-build-system>``` target build system can be ninja or make. Compiler-Collection can be gcc or clang. For example:

```build-linux.sh ninja```            -> it will choose gcc with ninja

```build-linux.sh make```             -> it will choose gcc with make

```build-linux.sh ninja gcc```        -> it will choose gcc with ninja

```build-linux.sh make gcc```         -> it will choose gcc with make

```build-linux.sh ninja clang```      -> it will choose clang with ninja

```build-linux.sh make clang```       -> it will choose clang with make

If you are not specify the build-target, it will choose ninja as default.

# LICENSE
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)
