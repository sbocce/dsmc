#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "solver.h"
#include "stat_tools.h"

solver::solver(sim_data* p_dat, mesh* p_msh, exporter* p_exp) : p_data(p_dat),
                                                                p_mesh(p_msh),
                                                                p_expt(p_exp),
                                                                timestep(0) { }

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

  // for each cell.... "id_c" stands for "id_cell"
  for(size_t id_c = 0; id_c < p_mesh->get_n_cells(); ++id_c) {

    p_cell = &(p_mesh->cells.at(id_c)); // pointer to the current cell

    // for each particle of the cell..... "id_p" stands for "id_particle"
    for(size_t id_p = 0; id_p < p_mesh->cells.at(id_c).particles.size(); ++id_p) {

      p_cell->advect_particle(id_p, p_data->get_dt(), p_data->get_sol_type());

    }

    // And once it's done, implement some kind of validation and export it!!!!!!
    if(p_data->get_png_flag()) {
      char integer_string[32];
      sprintf(integer_string, "%05d", timestep);
      char filename[512] = "./output/provaoutput";
      char extension[31] = ".png";
      strcat(filename, integer_string);
      strcat(filename, extension);
  
      p_expt->plot_particles_PNG(filename);
    }

  }

  // Is it in the same cell as before?
}

//------------------------------------------------------

void solver::collision_step()
{
  // SEE PAG 218, Bird
  // 
  cell* p_cell;
  double cell_pcp; // number of possible collision partners for the cell

  // variables related to the considered cell
  size_t Np;       // number of particles inside a cell
  double Vol;      // cell volume

  // FOR EACH CELL:
  for(size_t id_c = 0; id_c < p_mesh->get_n_cells(); ++id_c) {
    
    p_cell = &(p_mesh->cells.at(id_c)); // set pointer to the current cell

    // 1) Find how many collisions are to be computed
    //   1.1) compute (sigma cr)|max
    //   1.2) set cell_pcp according to NTC scheme

    Np  = p_cell->particles.size();
    Vol = p_cell->get_volume();

//    cell_pcp = 0.5*Np*(Np - 1)*Fnum*sigma_cr_max*dt/Vol;
 
    // 2) compute them..

  }
}
