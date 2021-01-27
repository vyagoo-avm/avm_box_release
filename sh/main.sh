#!/bin/sh
chmod 777 fullavm
export  QTDIR=/root/lib/qt
export QT_PLUGIN_PATH=${QTDIR}/plugins
export LD_LIBRARY_PATH=/lib:/usr/lib:/root/lib:${QTDIR}/lib:${LD_LIBRARY_PATH}
export QT_QWS_FONTDIR=${QTDIR}/lib/fonts
export QWS_DISPLAY="Transformed:LinuxFB:/dev/fb1:mmWidth600:0"
export QWS_KEYBOARD=linuxinput:/dev/input/event2 
./fullavm &
