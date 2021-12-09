#!/bin/bash

cd "$(dirname "$0")"
cd ../
./scripts/premake/Linux/premake5 gmake2
