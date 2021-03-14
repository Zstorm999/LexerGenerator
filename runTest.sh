#!/bin/bash

#building files
make

./test.out

rm test.out
rm *.d

echo "Done"