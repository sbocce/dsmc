# dsmc
horsing around with dsmc.

**COMPILING**

Just run 'make' in the main directory.
This will first of all compile lodepng, then it will go into src and compile the main program.
The executable is placed into the 'bin' directory.


**NOW DOING..**

I've implemented the walls.... but they don't work.

**COMMENTS AND USELESS STUFF**

Ok, for now the advection of particles is embrionally implemented in 1D.
The particles move and periodicity is applied in the Y and Z direction.
Some outputting is sput, so that I can check the directions.

*TODO 1*: implement what happens when a particle hits the x walls, that is
        it appears into another cell and disappears from the current one
        or bounces on the wall with a certain accommodation factor.

*TODO 2*: input file reader
