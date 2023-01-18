#!/bin/sh
gcc -Wall -pedantic -O2 -g ../ccheckmate.c arraytests.c primitivetests.c booltests.c -Wl,--wrap,main
./a.out
