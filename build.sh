#!/bin/sh
cd bindings
g++ -shared -std=c++11 -fPIC -I/system/develop/headers/python3.9m haiku.cpp -lbe -o haiku.so
mkdir ../bin
mv haiku.so ../bin
cd ..