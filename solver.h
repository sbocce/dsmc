#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <math.h>

#include "mesh.h"

class solver {

  public:
    solver(mesh* p_msh);
    ~solver(){};
    void initialize();
    void seed_particles();
    void translation_step();

  private:
    mesh* p_mesh; // pointer to the mesh
    double dt;    // timestep
};

#endif /* SOLVER_H */
