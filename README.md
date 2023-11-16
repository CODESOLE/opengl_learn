# OpenGL Learn

[![ci](https://github.com/codesole/opengl_learn/actions/workflows/ci.yml/badge.svg)](https://github.com/codesole/opengl_learn/actions?query=workflow%3Aci)
[![Build Status](https://travis-ci.com/CODESOLE/opengl_learn.svg?branch=main)](https://travis-ci.com/CODESOLE/opengl_learn)
[![CodeQL](https://github.com/CODESOLE/opengl_learn/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/CODESOLE/opengl_learn/actions/workflows/codeql-analysis.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/codesole/opengl_learn/badge)](https://www.codefactor.io/repository/github/codesole/opengl_learn)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/888554f6d27b47e6a55c8fc61de7bc66)](https://www.codacy.com/gh/CODESOLE/opengl_learn/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=CODESOLE/opengl_learn&amp;utm_campaign=Badge_Grade)
[![Coverity Scan](https://scan.coverity.com/projects/24005/badge.svg)](https://scan.coverity.com/projects/codesole-opengl_learn)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

OpenGL experimenting repo.

# Dependencies

 - [Meson](https://mesonbuild.com/Getting-meson.html)
 - For Windows -> [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)
 - [Git](https://git-scm.com/downloads) or [Github Desktop](https://desktop.github.com/)

 **Make sure these are installed and on your PATH.**
 
If you are on Windows 10 version 1709 and later, you can install this dependencies easily with this command (open cmd.exe or powershell.exe and type):
```shell
winget install --id Microsoft.VisualStudio.2022.BuildTools
winget install --id Git.Git
winget install --id mesonbuild.meson
```
Then:
```
git clone https://https://github.com/CODESOLE/opengl_learn.git
```


# Build Instructions For WINDOWS

Just Run:
```shell
.\build-windows.bat
```


# Build Instructions For LINUX

For Linux install build dependencies, for Ubuntu/Debian and its derivatives command is:

```shell
sudo apt update && sudo apt install libx11-xcb-dev libfontenc-dev libice-dev libsm-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxfixes-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxrandr-dev libxrender-dev libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxvmc-dev libxxf86vm-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev libxcb-cursor-dev libxcb-util-dev libxcb-util0-dev libgl-dev libgl1-mesa-dev libxkbcommon-dev
```

Just Run:
```shell
./build-linux.sh
```


# LICENSE

[![gpl-3.0](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)](https://www.gnu.org/licenses/gpl-3.0)
