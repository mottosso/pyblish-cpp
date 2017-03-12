@echo off
if not exist build mkdir build
pushd build
qmake ..
nmake
popd