#!/bin/bash

BUILDMODE="full"

if [ $1 ]
then
    if [ $1 == '--fast' ]
    then
        BUILDMODE="fast"
    fi
fi

if [ $BUILDMODE == "fast" ]
then
    echo "doing the fast test with 2 boards and 2 examles"
    boards="-b esp32dev -b ATmega1280"
    examples=("LedControllerDemoRocket" "LedControllerDemoHwSPI")
else
    echo "doing the full test with 5 boards and 4 examles"
    boards="-b esp32dev -b d1_mini -b uno -b ATmega1280 -b leonardo"
    examples=("LedControllerDemoRocket" "LedControllerDemoCounting" "LedControllerDemoHwSPI" "LCDemo7Segment")
fi

for i in "${examples[@]}"
do
	PLATFORMIO_CI_SRC="examples/$i/$i.ino" python3 -m platformio ci --lib="." ${boards} --keep-build-dir
    if [ $? -eq 1 ]
    then
        echo "error while building $i"
        exit 1
    fi
done

echo "running the native unit tests"
python3 -m platformio test -e native