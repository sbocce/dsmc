#ifndef SOLVER_H
#define SOLVER_H

#include "sim_data.h"
#include "mesh.h"
#include "exporter.h"

class solver {

  public:
    solver(sim_data* p_dat, mesh* p_msh, exporter* p_exp);
    ~solver(){};
    void seed_particles();
    void compute_n_steps(size_t n);
    void translation_step();
    void collision_step();

    size_t get_timestep(); // returns timestep

  private:
    sim_data* p_data;       // pointer to the data structure 
    mesh*     p_mesh;       // pointer to the mesh
    exporter* p_expt;       // pointer to the exporter object

    size_t      timestep;    // number of current timestep
};

#endif /* SOLVER_H */
