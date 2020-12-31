@echo off
mkdir build
cd build
START /WAIT cmake --build . --config Debug
cd ..
build\Game\Debug\game.exe