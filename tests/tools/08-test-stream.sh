#!/bin/sh
source ./config

LINK=`megals $ROPTS --export /Root/TestDir/test.dat | cut -d ' ' -f 1`

rm -f test-stream.dat
megaget $OPTS --path - /Root/TestDir/test.dat > test-stream.dat

cmp test.dat test-stream.dat || echo "=== FAILED ==="

rm -f test-stream.dat
megadl --path - "$LINK" > test-stream.dat

cmp test.dat test-stream.dat || echo "=== FAILED ==="
