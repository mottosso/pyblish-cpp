@echo off
if not exist build mkdir build
pushd build
qmake ..
nmake Debug && popd && echo Success! || ^
echo Failed.. && popd && exit /B 1