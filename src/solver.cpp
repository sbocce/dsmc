#include <iostream>
#include <math.h>

#include "solver.h"
#include "stat_tools.h"

solver::solver(mesh* p_msh) : p_mesh(p_msh) { }

//------------------------------------------------------

void solver::initialize()
{
std::cout << "Solver: reading input file..." << std::endl;

  std::cout << " ATTENTION: solver.initialize() should read an input file and pick the DeltaT for example!\n";
  std::cout << "            hard-coded for now!\n";

  dt = 0.001; // <<<-----------------  HHHAAAAAARD COOOODED!!!!!

  sol_type = "1D";
}

//------------------------------------------------------

void solver::seed_particles()
{
  int PARTICLES_PER_CELL = 12; // <<<<<<<<<<<<<<<<<<<<<<<<<------------------  !!!!!!
  double VEL_MAX_component = 100;

  // For each cell, fill it properly. "id_c" stands for "id_cell". "id_p" for "id_particle"
  double x, y, z, u, v, w;
  cell*     p_cell_now;
  particle  part_now;

  for(int id_c = 0; id_c < p_mesh->get_n_cells(); ++id_c) {
    // pointer to current cell
    p_cell_now = &( p_mesh->cells.at(id_c) );

    // create particles and assign them to the cell
    for(int id_p = 0; id_p < PARTICLES_PER_CELL; ++id_p) {
      // Generate particle position and velocity
      x = sample_uniform_dist(p_cell_now->XYZcorners[0], 
                              p_cell_now->XYZcorners[1]);
      y = sample_uniform_dist(p_cell_now->XYZcorners[2],
                              p_cell_now->XYZcorners[3]);
      z = sample_uniform_dist(p_cell_now->XYZcorners[4],
                              p_cell_now->XYZcorners[5]);

      u = sample_uniform_dist(-VEL_MAX_component, VEL_MAX_component);
      v = sample_uniform_dist(-VEL_MAX_component, VEL_MAX_component);
      w = sample_uniform_dist(-VEL_MAX_component, VEL_MAX_component);

      part_now.pos[0] = x;    part_now.pos[1] = y;    part_now.pos[2] = z;
      part_now.vel[0] = u;    part_now.vel[1] = v;    part_now.vel[2] = w;
  
      p_cell_now->particles.push_back(part_now);
    }
  }
}

//------------------------------------------------------

void solver::translation_step()
{
  // Working variables
  double    r_end[3];
  cell*     p_cell;
// REMOVE ME  //  particle* p_part;  

  // for each cell.... "id_c" stands for "id_cell"
  for(size_t id_c = 0; id_c < p_mesh->get_n_cells(); ++id_c) {

    p_cell = &(p_mesh->cells.at(id_c)); // pointer to the current cell

    // for each particle of the cell..... "id_p" stands for "id_particle"
    for(size_t id_p = 0; id_p < p_mesh->cells.at(id_c).particles.size(); ++id_p) {

      p_cell->advect_particle(id_p, dt, sol_type);

    }

    // And once it's done, implement some kind of validation and export it!!!!!!
    
    // [... export ...]
    
 
  }

  // Is it in the same cell as before?
}


