#!/bin/sh
gcc -Wall -pedantic -O2 -g ../ccheckmate.c example.c -Wl,--wrap,main
./a.out
