#!/bin/bash

cd "$(dirname "$0")"
cd ../
./scripts/premake/mac/premake5 xcode4
