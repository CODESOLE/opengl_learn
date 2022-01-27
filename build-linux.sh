#!/bin/sh

if [ -z "$2" ]
then
  printf "\nCOMPILER NOT SPECIFIED. BUILDING WITH GCC DEFAULT\n"
  CC=gcc
elif [ "$2" = "gcc" ]
then
  printf "\nCOMPILING WITH GCC\n"
  CC=gcc
else
  printf "\nCOMPILING WITH CLANG\n"
  CC=clang
fi

if [ -z "$1" ]
then
  printf "\nBUILD SYSTEM NOT SPECIFIED. BUILDING WITH NINJA DEFAULT\n"
  mkdir -p build
  rm -rfd build/*
  cd build
  cmake -G Ninja -DCMAKE_C_COMPILER=${CC} -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. && ninja
elif [ "$1" = "ninja" ]
then
  printf "\nBUILDING WITH NINJA\n"
  mkdir -p build
  rm -rfd build/*
  cd build
  cmake -G Ninja -DCMAKE_C_COMPILER=${CC} -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. && ninja
else
  printf "\nBUILDING WITH MAKE\n"
  mkdir -p build
  rm -rfd build/*
  cd build
  cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=${CC} -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. && make
fi
