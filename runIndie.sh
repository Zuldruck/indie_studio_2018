#!/usr/bin/env bash

mkdir build
cd build
if [[ "$OSTYPE" != "linux-gnu" ]] && [[ "$OSTYPE" != "darwin"* ]]; then
    cmake -G "Visual Studio 15 2017" ..
else
    if [[ $1 == "doc" ]]; then
        cmake .. -DGENERATE_DOC=ON
        make
        exit
    fi
    cmake .. -DGENERATE_DOC=OFF
    make
    cp ./bomberman ../
    cd ..
    if [[ $1 == "valgrind" ]];then
        valgrind ./bomberman
    elif [[ $1 == "advanced_valgrind" ]];then
        valgrind --leak-check=full --show-leak-kinds=all ./bomberman
    else
        ./bomberman
    fi
fi