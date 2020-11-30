#!/bin/bash
CC="gcc -m64 " TARGET_EXEC="x86_64" make
CC="gcc -m32 " TARGET_EXEC="i386" make
CC="arm-linux-gnueabihf-gcc" TARGET_EXEC="arm" make

