@echo off
mkdir build
cd build
START /WAIT cmake --build . --config Debug
cd ..
build\Debug\game.exe