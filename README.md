# GalaxySim
Project simulating galaxies for a modelling &amp; simulation course at RUG.


## C implementation
The C code for this project is in the `/c` folder. It *should* be able to compile with any C compiler and has no external dependencies outside the regular libraries. Simply `make` the source code and run the program `./nbody`.

The program generates a lot (500) of image frames. They can be combined into an animated GIF using [ImageMagick](https://imagemagick.org) using:

    convert -delay 4 -loop 0 *.pgm image.gif
**Note:** there are many ways to install ImageMagick. On a Mac with [Homebrew](https://brew.sh) you can simply `brew install imagemagick`.

![One of the first attempts at a spiral galaxy](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/aspiral7.gif "One of the first attempts at a spiral galaxy")