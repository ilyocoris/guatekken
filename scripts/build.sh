#!/bin/sh
# sudo ./scripts/build.sh
ls
if [ -d "game_build" ]; then
    rm -r game_build
fi
mkdir game_build
ls
cp -r game/Builds/Build game/Builds/TemplateData game_build
cp frontend/index.html game_build
cp -r frontend/js game_build/js
# (
#     cd game_build
#     python3 -m http.server
# )
