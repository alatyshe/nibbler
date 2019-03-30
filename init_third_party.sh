git submodule sync && git submodule update --init --recursive

if brew ls --versions sdl2_ttf > /dev/null; then
    echo "SDL2 installed";
else
    brew install sdl2_ttf
fi