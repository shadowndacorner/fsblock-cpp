@echo off

:loop
pushd build
ninja
cd ..\bin
fsblock.exe -p ..\src
popd
REM goto loop