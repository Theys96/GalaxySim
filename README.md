# GalaxySim
Project simulating galaxies for a modelling &amp; simulation course at RUG.


## C implementation
The C code for this project is in the `/c` folder. It *should* be able to compile with any C compiler and has no external dependencies outside the regular libraries. Simply `make` the source code and run the program `./nbody`.

The program generates a lot (500) of image frames. They can be combined into an animated GIF using [ImageMagick](https://imagemagick.org) using:

    convert -delay 4 -loop 0 *.pgm image.gif
**Note:** there are many ways to install ImageMagick. On a Mac with [Homebrew](https://brew.sh) you can simply `brew install imagemagick`.

First animations:

![Animation 1](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation1.gif "Animation 1")
![Animation 2](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation2.gif "Animation 2")
![Animation 3](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation3.gif "Animation 3")

First attempts at "galaxies":

![Galaxy attempt 1](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation4.gif "Galaxy attempt 1")
![Galaxy attempt 2](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation5.gif "Galaxy attempt 2")

First seemingly stable attempt with a suppermassive object in the center:

![Galaxy](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation6.gif "Galaxy")

Disrupting galaxies for cool effects:

![Disrupted galaxy 1](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation7.gif "Disrupted galaxy 1")
![Disrupted galaxy 2](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation8.gif "Disrupted galaxy 2")

Galaxy with stars of variable mass:
![Galaxy with stars of variable mass](https://raw.githubusercontent.com/Theys96/GalaxySim/thijs/c/animation9.gif "Galaxy with stars of variable mass")
