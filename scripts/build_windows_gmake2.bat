@echo off
pushd %~dp0\..\
call scripts\premake\windows\premake5.exe gmake2
popd
PAUSE
