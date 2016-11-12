#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "solver.h"
#include "stat_tools.h"

solver::solver(mesh* p_msh, exporter* p_exp) : p_mesh(p_msh),
                                               p_expt(p_exp),
                                               timestep(0) { }

//------------------------------------------------------

void solver::initialize()
{
std::cout << "Solver: reading input file..." << std::endl;

  std::cout << " ATTENTION: solver.initialize() should read an input file and pick the DeltaT for example!\n";
  std::cout << "            hard-coded for now!\n";

  dt = 0.0001; // <<<-----------------  HHHAAAAAARD COOOODED!!!!!

  sol_type = "1D";
}

//------------------------------------------------------

void solver::seed_particles()
{
  int PARTICLES_PER_CELL = 50; // <<<<<<<<<<<<<<<<<<<<<<<<<------------------  !!!!!!
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

      part_now.set_mass(5.31e-26); // Mass of O2 molecule..

      p_cell_now->particles.push_back(part_now);
    }
  }
}

//------------------------------------------------------

size_t solver::get_timestep()
{
  return this->timestep;
}

//------------------------------------------------------

void solver::compute_n_steps(size_t n)
{
  for(size_t t_id = 0; t_id < n; ++t_id)
  {
    std::cout << "Solving step: " << t_id << " of " << n - 1 << std::endl;
    
    // Translation step
    translation_step();

    // Collision step
    collision_step();

    // One timestep has been performed. Adjourn the timestep variable
    timestep++;
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
    char integer_string[32];
    sprintf(integer_string, "%05d", timestep);
    char filename[512] = "../output/provaoutput";
    char extension[31] = ".png";
    strcat(filename, integer_string);
    strcat(filename, extension);

    p_expt->plot_particles_PNG(filename);

  }

  // Is it in the same cell as before?
}

//------------------------------------------------------

void solver::collision_step()
{
  // SEE PAG 218, Bird
  // 
}
