#!/bin/bash

cd "$(dirname "$0")"
cd ../
./scripts/premake/linux/premake5 gmake2
 read -s -n 1 -p "Press any key to continue . . ."
 echo ""

