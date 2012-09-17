#!/bin/sh

tar xvfj lib.tar.bz2
sudo mkdir /opt/dial-up
sudo cp -n dial-up dial-up.png install.sh README /opt/dial-up

cd lib

sudo cp -n  libQtGui.so.4 libQtNetwork.so.4 libQtCore.so.4 libstdc++.so.6 /usr/lib/
sudo cp -n  libfontconfig.so.1  libaudio.so.2  libfreetype.so.6  libgobject-2.0.so.0 /usr/lib/
sudo cp -n  libSM.so.6  libICE.so.6  libXrender.so.1  libXext.so.6  libX11.so.6  /usr/lib/
sudo cp -n  libgthread-2.0.so.0  libXt.so.6  libXau.so.6  libxcb.so.1  libXdmcp.so.6  /usr/lib/

sudo cp -n  libpthread.so.0   libm.so.6  libc.so.6  libdl.so.2  librt.so.1   /lib/tls/i686/cmov/
sudo cp -n  libgcc_s.so.1  libglib-2.0.so.0  libpng12.so.0  libz.so.1  ld-linux.so.2  libexpat.so.1  libpcre.so.3  libuuid.so.1 /lib/
 
sudo cp -n   dial-up.desktop  ~/.local/share/applications/
