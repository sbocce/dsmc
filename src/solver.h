#ifndef SOLVER_H
#define SOLVER_H

#include "mesh.h"
#include "exporter.h"

class solver {

  public:
    solver(mesh* p_msh, exporter* p_exp);
    ~solver(){};
    void initialize();
    void seed_particles();
    void compute_n_steps(size_t n);
    void translation_step();
    void collision_step();

    size_t get_timestep(); // returns timestep

  private:
    mesh*     p_mesh;      // pointer to the mesh
    exporter* p_expt;       // pointer to the exporter object

    double      dt;          // value of timestep
    size_t      timestep;    // number of current timestep
    const char* sol_type;    // 1D or 2D or 2D axisimmetric or 3D
};

#endif /* SOLVER_H */
