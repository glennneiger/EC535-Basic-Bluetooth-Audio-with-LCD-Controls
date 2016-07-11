#!/bin/bash

# Prepare gumstix and touchscreen interface
export QT_QWS_FONTDIR=/media/card/lib/fonts
export QWS_MOUSE_PROTO='tslib:/dev/input/touchscreen0'
ts_calibrate

# Run GUI
/media/card/project/scripts/qt -qws
