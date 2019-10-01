# GalaxySim
Project simulating galaxies for a Modelling &amp; Simulation course at RUG.


## C implementation
The C code for this project is in the `/src` folder. It *should* be able to compile with any C compiler and has no external dependencies outside the regular libraries. Simply `make` the source code and run the program `./nbody`.

The program generates a lot (500) of image frames. They can be combined into an animated GIF using [ImageMagick](https://imagemagick.org) by running:

    make gif

**Note:** there are many ways to install ImageMagick. On a Mac with [Homebrew](https://brew.sh) you can simply `brew install imagemagick`.

To get rid of all those .pgm images, simply run `make clean`.

Animation example:

![Example animation](https://raw.githubusercontent.com/Theys96/GalaxySim/develop/src/img/image.gif "Example animation")
