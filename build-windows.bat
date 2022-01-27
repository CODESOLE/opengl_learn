@echo off

setlocal EnableDelayedExpansion

set CC="gcc" 

IF [%2]==[] (
IF NOT "%1"=="msbuild" (
ECHO.
ECHO COMPILER NOT SPECIFIED. BUILDING WITH GCC DEFAULT
ECHO.
)
  set CC="gcc" 
)

IF "%2"=="gcc" (
IF NOT "%1"=="msbuild" (
ECHO.
ECHO COMPILING WITH GCC
ECHO.
)
  set CC="gcc" 
)

IF "%2"=="clang" (
IF NOT "%1"=="msbuild" (
ECHO.
ECHO COMPILING WITH CLANG
ECHO.
)
  set CC="clang" 
)

IF [%1]==[] (
ECHO.
ECHO BUILD SYSTEM NOT SPECIFIED. BUILDING WITH NINJA DEFAULT
ECHO.

set folder=".\build"

IF NOT EXIST !folder! (
    md !folder!
)

IF EXIST !folder! (
    cd /d !folder!
    for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)

    cmake.exe -G Ninja -DCMAKE_C_COMPILER=!CC! -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

    cmake --build .
)

goto EOF
)

IF "%1"=="ninja" (
ECHO.
ECHO BUILDING WITH NINJA
ECHO.

set folder=".\build"

IF NOT EXIST !folder! (
    md !folder!
)

IF EXIST !folder! (
    cd /d !folder!
    for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)

    cmake.exe -G Ninja -DCMAKE_C_COMPILER=!CC! -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

    cmake --build .
)

goto EOF
)

IF "%1"=="make" (
ECHO.
ECHO BUILDING WITH MAKE
ECHO.

set folder=".\build"

IF NOT EXIST !folder! (
    md !folder!
)

IF EXIST !folder! (
    cd /d !folder!
    for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)

    cmake.exe -G "Unix Makefiles" -DCMAKE_C_COMPILER=!CC! -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

    cmake --build .
)

goto EOF
)

IF "%1"=="msbuild" (
ECHO.
ECHO CREATING BUILD FILES WITH MSBUILD
ECHO.

set folder=".\buildMSBuild"

IF NOT EXIST !folder! (
    md !folder!
)

IF EXIST !folder! (
    cd /d !folder!
    for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)

    cmake.exe ..

    cmake --build .
)

goto EOF
)
:EOF
