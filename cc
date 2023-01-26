#!/bin/sh

cc -g "src/$1.cpp" -o bin/$1
bin/$1
