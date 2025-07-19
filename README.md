# tbsprpg_sdl

### Setup library directory
```shell
mkdir -p lib/arm64/include
```

### Building SDL2
```shell
sudo apt install xorg-dev libudev-dev libgl1-mesa-dev libglu1-mesa-dev libasound2-dev libpulse-dev libopenal-dev libogg-dev libvorbis-dev libpng-dev libfreetype6-dev zlib1g-dev

git clone https://github.com/libsdl-org/SDL.git
cd SDL
git checkout tags/release-2.32.8
mkdir build
cd build
cmake .. -DSDL_STATIC=OFF -DCMAKE_INSTALL_PREFIX=/home/david/Projects/tbsprpg_sdl/lib/arm64
make
make install
```

### SDL Mixer
```shell
git clone https://github.com/libsdl-org/SDL_mixer.git
cd SDL_mixer
git checkout tags/release-2.8.1
cd external
./download.sh
cd ..
mkdir build
cd build
#cmake .. -DSDL2_DIR=/home/david/Projects/tbsprpg_sdl/lib/arm64/lib/cmake/SDL2 -DSDL2MIXER_VENDORED=ON SHARED_LIBS=OFF -DSDL2MIXER_DEPS_SHARED=OFF -DCMAKE_INSTALL_PREFIX=/home/david/Projects/tbsprpg_sdl/lib/arm64
cmake .. -DSDL2_DIR=/home/david/Projects/tbsprpg_sdl/lib/arm64/lib/cmake/SDL2 -DSDL2MIXER_VENDORED=ON -DCMAKE_INSTALL_PREFIX=/home/david/Projects/tbsprpg_sdl/lib/arm64
make
make install
```

### SDL Image
```shell
sudo apt install nasm
git clone https://github.com/libsdl-org/SDL_image.git
cd SDL_image
git checkout tags/release-2.8.8
cd external
./download.sh
cd ..
mkdir build
cd build
#cmake .. -DSDL2_DIR=/home/david/Projects/tbsprpg_sdl/lib/arm64/lib/cmake/SDL2 -DSDL2IMAGE_VENDORED=ON -DBUILD_SHARED_LIBS=OFF -DSDL2IMAGE_DEPS_SHARED=OFF -DCMAKE_INSTALL_PREFIX=/home/david/Projects/tbsprpg_sdl/lib/arm64
cmake .. -DSDL2_DIR=/home/david/Projects/tbsprpg_sdl/lib/arm64/lib/cmake/SDL2 -DSDL2IMAGE_VENDORED=ON -DBUILD_SHARED_LIBS=OFF -DSDL2IMAGE_DEPS_SHARED=OFF -DCMAKE_INSTALL_PREFIX=/home/david/Projects/tbsprpg_sdl/lib/arm64
make
make install
```