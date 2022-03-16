# fdf

![fdf](https://user-images.githubusercontent.com/73375669/158503585-21684875-12a2-4a95-9ed3-02d8e16444e8.gif)

## Description
fdf is a very simple wire frame viewer written in C.
The following operations are supported.

- zoom
- rotation
- shift

## Requirement
- OS X, linux
- C compiler
- make
- X Window System

You need `XQuartz` to build on mac. Please install it with `brew` or similar.

``` sh
brew install --cask xquartz
```

## Build
Execute the following command in the appropriate directory.

``` sh
https://github.com/Yamada-Ika/fdf.git
cd fdf
make
```

## Usage
In the directory where `fdf` exists, execute the following command.
If you do not see the screen, run `xeyes` to see if XQuartz is available.

``` sh
./fdf map/42.fdf
```

## Features
- zoom
  - Mouse wheel can be operated to zoom in and out around the mouse cursor.
![fdf_zoom_10](https://user-images.githubusercontent.com/73375669/158503722-7be4d449-8c1f-4904-b1c7-bf0feedf0f4e.gif)

- rotation
  - Rotate with `x,y,z` keys
![fdf_rotate_10](https://user-images.githubusercontent.com/73375669/158503683-5b0ee432-64df-453a-80e6-a14caf4a10cd.gif)

- shift
  - Arrow keys can be used to move objects
![fdf_shift_10](https://user-images.githubusercontent.com/73375669/158503667-6a96d18c-5aaa-4426-9547-751ba810b078.gif)

## Licence
This software is released under the MIT License, see LICENSE.
