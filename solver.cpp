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

      u = sample_uniform_dist(0, VEL_MAX_component);
      v = sample_uniform_dist(0, VEL_MAX_component);
      w = sample_uniform_dist(0, VEL_MAX_component);

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
  particle* p_part;  

  bool x_is_in, y_is_in, z_is_in;

  // for each cell.... "id_c" stands for "id_cell"
  for(size_t id_c = 0; id_c < p_mesh->get_n_cells(); ++id_c) {

    p_cell = &(p_mesh->cells.at(id_c)); // pointer to the current cell

    // for each particle of the cell..... "id_p" stands for "id_particle"
    for(size_t id_p = 0; id_p < p_mesh->cells.at(id_c).particles.size(); ++id_p) {

      // ---------------------------------------------------------------------------------
      // 1) try to translate the particle
      // 2) is it still in the cell? Great, update the position and skip to the next one! :D
      // 3) if it is out of the cell:
      //  3.1) find which surface was crossed (boh.. I can maybe compare angles..)
      //  3.2) is it a standard face?
      //       yes -> find the neighboring cell and put it inside it (where? Throw a warning if the
      //              translation exceeds it! WARNING: timestep too big! One cell skipped around
      //              x = ..., y = ..., z = ...)    
      //  3.3) is it a boundary face? What kind?
      //    3.2.1) if it is inflow/outflow face, then just pop out this particle (it went out of the
      //           domain! It deserves it!
      //    3.2.2) if it is a solid boundary, reflect it or let it bounce according to the specified
      //           accommodation factor
      //    3.2.3) if it is a periodic BC, move it to the cell's "periodic mate"
      //  --------------------------------------------------------------------------------
  
      // Point the pointer to the current particle
      p_part = &(p_mesh->cells.at(id_c).particles.at(id_p));

      // ========   Point 1)   ===================
      // ====  try to translate the particle  ====
      p_part->advect(dt, r_end);

      std::cout << "DB: " << p_part->pos[0] << " " << p_part->pos[1] << " " << p_part->pos[2] << std::endl;
      std::cout << "DB: " << p_part->vel[0] << " " << p_part->vel[1] << " " << p_part->vel[2] << std::endl;
      std::cout << "DB: " << r_end[0] << " " << r_end[1] << " " << r_end[2] << std::endl;
      std::cout << "\n";

      // =======   Point 2)   =====================
      // ===  Check if I'm still in the cell  =====

      x_is_in = (r_end[0] < p_cell->XYZcorners[1]) && (r_end[0] > p_cell->XYZcorners[0]);
      y_is_in = (r_end[1] < p_cell->XYZcorners[3]) && (r_end[1] > p_cell->XYZcorners[2]);
      z_is_in = (r_end[2] < p_cell->XYZcorners[5]) && (r_end[2] > p_cell->XYZcorners[4]);

      if( x_is_in && y_is_in && z_is_in  ) {
        // adjourn particle position, then switch to the next particle
        p_part->pos[0] = r_end[0];
        continue;
      }

      // =======   Point 3)   =====================
      // ====  If I'm out of the cell..   =========
      // !!!!!!!!!!!   THIS IS GOING TO WORK ONLY FOR 1D CASE   !!!!!!!!!!!!!!!!
      // !!!!!!!!!!!   3.1) process y and z with the MODULUS function
      // y_new = y_bottom + (y - y_bottom) % l_side
      // #include <math.h>;  then use fmod(x, y)  === x % y for doubles

      // y AND z ARE SYMMETRY AND I'M IN 1D
      if( !y_is_in ) {
	      r_end[1] = p_cell->XYZcorners[2] + fmod(r_end[1] - p_cell->XYZcorners[2], p_cell->get_side(1));
      }
      if( !z_is_in ) {
	      r_end[2] = p_cell->XYZcorners[4] + fmod(r_end[2] - p_cell->XYZcorners[4], p_cell->get_side(2));
      }
      if( !x_is_in) { // neighboring cell? Reflecting surface?

        // [...]

        // If the particle has exited, REMOVE IT FROM THE CELL!
      }


      // And once it's done, implement some kind of validation and export it!!!!!!
    }
 
  }

  // Is it in the same cell as before?
}


