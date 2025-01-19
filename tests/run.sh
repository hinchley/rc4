#!/bin/sh

gcc -o tests tests.c -Werror -Wall -Wpedantic && ./tests
rm tests
