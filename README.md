# dsmc
horsing around with dsmc.

**COMPILING**

Just run 'make' in the main directory.
This will first of all compile lodepng, then it will go into src and compile 
the main program.
The executable is placed into the 'bin' directory.


**NOW DOING..**

Implementing HS collision model..

**COMMENTS AND USELESS STUFF**

Ok, for now the advection of particles is implemented in 1D.
The particles move and periodicity is applied in the Y and Z direction.
The istantaneous state is plotted on a PNG image.

*TODO 1*: implement a counter, that spits the TOTAL NUMBER OF PARTICLES,
          because before proceeding I'd like to be sure that I've 
          implemented the "add particle()" and "pop particle()" in a 
          reasonable way!!!!!!!!!!!!!!!!!

*TODO 2*: implement some function that may compute and extract values from 
          the cells

*TODO 3*: implement a better wall bouncing! MAXWELL MODEL for example. Mine
          is too naive I guess..

*TODO 4*: input file reader. Insert argc, argv[] and pass the filename to
          the solver's constructor. In the solver::initialize() function
          call the file_reader and pick required values.

*TODO 5*: implement collisions. Take a look at Handbook of Fluid Dynamics,
          by Johnson. Has a chapter about it. Seems very practical.

**FUTURE WORK and NOTES FOR ME**

---

First of all, consider replacing all the rand() with a good random number
generator!
Use Boost::Random for example.. or take a look at the Mersenne Twister.
C++11 implements a lot of stuff in <random>.
Supposedly nice paper about pseudo-random numbers generation: 
http://lammps.sandia.gov/threads/pdfFowF57Qu9A.pdf

---

Currently, when a particle moves from one cell to another, it's removed 
from this cell: since it's a part of a vector, the position is freed and 
all the subsequent particles are shifted up of one position.
I guess this takes a lot of time.. It might be more efficient to assign 
a bool variable to each particle, like "DoIExist". Deleting the particle
means assigning the value 0 to "DoIExist".
Once deleted, if a new particle enters a cell, it's assigned the first
free position, i.e. the first particle that has DoIExist == 0 is totally
rewritten.
Of course, every statistics is performed only on existing particles.
