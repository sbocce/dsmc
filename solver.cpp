#include "solver.h"
#include "stat_tools.h"

solver::solver(mesh* p_msh) : p_mesh(p_msh) { }

//------------------------------------------------------

void solver::seed_particles()
{
  int PARTICLES_PER_CELL = 12; // <<<<<<<<<<<<<<<<<<<<<<<<<------------------  !!!!!!
  double VEL_MIN = 90;
  double VEL_MAX = 110;

  // For each cell, fill it properly. "id_c" stands for "id_cell". "id_p" for "id_particle"
  double x, y, z, u, v, w;
  cell*     p_cell_now;
  particle  part_now;

  for(int id_c = 0; id_c < p_mesh->get_n_cells(); ++id_c) {
    // pointer to current cell
    p_cell_now = &( p_mesh->cells.at(id_c) );

    // create particles and assign them to the cell
    for(int id_p = 0; id_p < PARTICLES_PER_CELL; ++id_p) {
      // Generate a particle
      x = sample_uniform_dist(p_cell_now->XYZcorners[0], 
                              p_cell_now->XYZcorners[1]);
      y = sample_uniform_dist(p_cell_now->XYZcorners[2],
                              p_cell_now->XYZcorners[3]);
      z = sample_uniform_dist(p_cell_now->XYZcorners[4],
                              p_cell_now->XYZcorners[5]);

      u = sample_uniform_dist(VEL_MIN, VEL_MAX);
      v = sample_uniform_dist(VEL_MIN, VEL_MAX);
      w = sample_uniform_dist(VEL_MIN, VEL_MAX);

      part_now.pos[0] = x;    part_now.pos[1] = y;    part_now.pos[2] = z;
      part_now.vel[0] = u;    part_now.vel[1] = v;    part_now.vel[2] = w;
  
      p_cell_now->particles.push_back(part_now);
    }
  }
}


