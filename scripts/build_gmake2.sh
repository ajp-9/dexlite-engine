#!/bin/bash

cd "$(dirname "$0")"
cd ../
./scripts/premake/premake5 gmake2
