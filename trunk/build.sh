#!/bin/sh
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
export BUILD_WINDOWED=y
export BUILD_NOMOUSEGRAB=y
export BUILD_SDLDEBUG=-
./build $*

