#!/usr/bin/env bash

if [ -d "build" ]; then
  rm -rf build
fi

ls bomberman &> /dev/null
if [[ $? -eq 0 ]]; then
   rm -rf bomberman
fi
rm -rf cmake-build-debug
