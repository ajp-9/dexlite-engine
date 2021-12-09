#!/bin/bash

cd "$(dirname "$0")"
cd ../
./scripts/premake/MacOS/premake5 xcode4
