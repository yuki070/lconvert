#!/bin/sh
../src/lconvert ./test.lua ./a ./b -p BRANCH GZ
if [ $? -ne 0 ]; then
    echo "FAIL"
    exit 1
else
    echo "OK"
    cat ./b
fi
