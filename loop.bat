@echo off

echo Development loop
:loop
pushd build
ninja
popd

.\bin\fsblock.exe -p test
fsblock -p src -v -f
goto loop