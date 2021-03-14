#!/bin/bash

cc="g++"
exec="lexergenerator"
ccflags="-I includes -Wall -std=c++11"
llflags=""

mkdir build
mkdir build/source

$cc $ccflags -o build/main.o -c main.cpp

for file in source/*.cpp
do 
    len=${#file}
    name=${file:7:len-11}
    
    if [[ ! $name =~ [tT][eE][sS][tT] ]] 
    then

        $cc $ccflags -o build/source/$name.o -c $file
    fi
done

obj=`ls -dx build/source/*.*`
obj=${obj}" build/main.o"

$cc $ccflags $llflags -o $exec $obj 

echo "Build finished"
