#!/bin/sh
cd release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
