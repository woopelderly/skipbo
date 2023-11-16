# Cinder Setup
I forked the Cinder repo so it could buidl with C++17 without affecting skipbo's compiler flags.  Otherwise Cinder kept this project at C++17.  The fork is here:  https://github.com/woopelderly/Cinder

## Step 1
Clone Cinder from https://github.com/woopelderly/Cinder to a directory next to where you clone this project.  So, if you cloned this project to /home/<username>/src/skipbo, then clone Cinder to /home/<username>/src/Cinder.

```shell
$ cd /home/<username>/src
$ git clone --recursive -b master https://github.com/woopelderly/Cinder.git
```

## Step 2
Install the Cinder dependencies for the system you are on.  You may have to google this but as of 11-14-2023, these are the ubuntu and fedora dependencies.

### Ubuntu
https://libcinder.org/docs/guides/linux-notes/ubuntu.html

Cinder dependencies:
sudo apt-get install libxcursor-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    zlib1g-dev \
    libfontconfig1-dev \
    libmpg123-dev \
    libsndfile1 \
    libsndfile1-dev \
    libpulse-dev \
    libasound2-dev \
    libcurl4-gnutls-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-bad1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-libav \
    gstreamer1.0-alsa \
    gstreamer1.0-pulseaudio \
    gstreamer1.0-plugins-bad \
    libboost-filesystem-dev

git clone --recursive https://github.com/cinder/Cinder.git

### Fedora
https://github.com/cinder/Cinder/wiki/Cinder-for-Linux-%7C-Fedora-23-24-on-x86_64

Enable rpmfusion

Cinder dependencies:
sudo dnf install \
        mesa-libGL-devel \
        mesa-libGLU-devel \
        zlib-devel \
        libcurl-devel \
        pulseaudio-libs-devel \
        libmpg123-devel \
        libsndfile-devel \
        libXcursor-devel \
        libXrandr-devel \
        libXinerama-devel \
        libXi-devel \
        gstreamer1-devel \
        gstreamer1-plugins-base-devel \
        gstreamer1-plugins-bad-free-devel \
        fontconfig-devel

git clone --recursive -b master https://github.com/cinder/Cinder.git

## Step 3
Run cmake for Cinder for Debug and Release
```shell
$ cd /home/<username>/src/Cinder
$ cmake -B cmake -D CMAKE_BUILD_TYPE=Debug
$ cmake --build cmake --parallel
$ cmake -B cmake -D CMAKE_BUILD_TYPE=Release
$ cmake --build cmake --parallel
```

## Step 4
Run cmake for this project and build it.
```shell
$ cd /home/<username>/src/skipbo
$ cmake -B cmake -D CMAKE_BUILD_TYPE=Debug
$ cmake --build cmake --parallel
$ cmake -B cmake -D CMAKE_BUILD_TYPE=Release
$ cmake --build cmake --parallel
```
