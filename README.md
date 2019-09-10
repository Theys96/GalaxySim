# GalaxySim
Project simulating galaxies for a modelling &amp; simulation course at RUG.


## C implementation
The C code for this project is in the `/c` folder. It *should* be able to compile with any C compiler and has no external dependencies outside the regular libraries. Simply `make` the source code and run the program `./nbody`.

The program generates a lot (500) of image frames. They can be combined into an animated GIF using [ImageMagick](https://imagemagick.org) using:

    convert -delay 4 -loop 0 *.pgm image.gif
**Note:** there are many ways to install ImageMagick. On a Mac with [Homebrew](https://brew.sh) you can simply `brew install imagemagick`.

Animation examples:

![Animation 1](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation1.gif?token=ACJ6VJJVK5AN4FAQKQVTCWC5PAOM4 "Animation 1")
![Animation 2](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation2.gif?token=ACJ6VJLHDMNLDJAE3T4IIP25PAOQU "Animation 2")
![Animation 3](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation3.gif?token=ACJ6VJL63COUDZPWW74VFUS5PAOPQ "Animation 3")