# fdf

![fdf_10](https://user-images.githubusercontent.com/73375669/158502364-f950b6d3-907a-461b-b35f-db22a343fb97.gif)

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
![fdf_zoom_10](https://user-images.githubusercontent.com/73375669/158502220-280c1da1-5d8e-4839-8bed-15c85aa421a7.gif)

- rotation
  - Rotate with `x,y,z` keys
![fdf_rotate_10](https://user-images.githubusercontent.com/73375669/158502056-e99c2d3e-fa2c-4514-a297-c594ba09a83d.gif)

- shift
  - Arrow keys can be used to move objects
![fdf_shift_10](https://user-images.githubusercontent.com/73375669/158501926-ba6ebf3e-805a-4685-a11f-c356aaa56274.gif)

## Licence
This software is released under the MIT License, see LICENSE.
