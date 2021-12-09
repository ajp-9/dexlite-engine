@echo off
pushd %~dp0\..\
call scripts\premake\Windows\premake5.exe gmake2
popd
PAUSE
