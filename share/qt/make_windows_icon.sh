#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/kmushicoin.ico

convert ../../src/qt/res/icons/kmushicoin-16.png ../../src/qt/res/icons/kmushicoin-32.png ../../src/qt/res/icons/kmushicoin-48.png ${ICON_DST}
