#ifndef SOLVER_H
#define SOLVER_H

#include "mesh.h"

class solver {

  public:
    solver(mesh* p_msh);
    ~solver(){};
    void initialize();
    void seed_particles();
    void translation_step();

  private:
    mesh* p_mesh;          // pointer to the mesh
    double dt;             // timestep
    const char* sol_type;  // 1D or 2D or 2D axisimmetric or 3D
};

#endif /* SOLVER_H */
