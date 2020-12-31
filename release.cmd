@echo off
mkdir build
cd build
START /WAIT cmake --build . --config Release
cd ..
build\Game\Release\game.exe