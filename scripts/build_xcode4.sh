#!/bin/sh
pushd %~dp0\..\
scripts\premake\premake5 xcode4
popd
PAUSE
