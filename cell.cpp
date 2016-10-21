#include <stdlib.h>     /* exit, EXIT_FAILURE */

#include "cell.h"

// --------------------------------------------

void cell::set_id(size_t cell_id)
{
  this->id = cell_id;
}

// --------------------------------------------

size_t cell::get_id()
{
  return this->id;
}

// --------------------------------------------

void cell::compute_sides()
{
  this->len_sides[0] = (XYZcorners[1] - XYZcorners[0]);
  this->len_sides[1] = (XYZcorners[3] - XYZcorners[2]);
  this->len_sides[2] = (XYZcorners[5] - XYZcorners[4]);

  // Check if any side is negative or zero length and throw an error in this case
  if( (this->len_sides[0] <= 0) || (this->len_sides[1] <= 0) || (this->len_sides[2] <=0) )
  {
    std::cerr << std::endl;
    std::cerr << "ERROR! One side of cell " << this->id << " has size zero or negative!" << std::endl;
    std::cerr << "       Check that its corners are 'strictly increasing'" << std::endl;
    std::cerr << std::endl;

    exit(EXIT_FAILURE);
  }
}

// --------------------------------------------

double cell::get_side(size_t side_id)
{
  // side_id = 0 ----> x side
  // side_id = 1 ----> y side
  // side_id = 2 ----> z side

  return this->len_sides[side_id];
}

// --------------------------------------------

double cell::get_volume()
{

  std::cout << "IMPLEMENT ME!!!!" << std::endl;

  return -666.; // il numero della bestia

}

// --------------------------------------------

void cell::advect_particle(size_t particle_id, double dt)
{
  // --------------------------------------------------------------------------
  // The following is done for each direction independently 
  // (SHOULD BE OK FOR SMALL DISPLACEMENTS)
  // 
  // 0) for each direction..
  //
  // 1) try to translate the particle
  //
  // 2) did it exit the cell?
  //
  //   2.1) no  -> great, update the position and skip to the next cell
  //   2.2) yes -> ouch..
  //
  //     2.2.1) find out which face was crossed (first or second)
  //     2.2.2) act accordingly:
  //            - Free face:    move particle to the neighboring cell
  //            - Outflow face: just remove the particle
  //            - Solid wall:   re-emit the particle inside the cell with a velocity 
  //                            given by temperature and accommodation factor
  // --------------------------------------------------------------------------

  double new_pos[3];

std::cout << "DB: Advecting particle " << particle_id << std::endl;

  for(size_t id_dir = 0; id_dir < 3; ++id_dir) { // for each direction.. x, y, z
 
    // try to update position 
    new_pos[id_dir] =   particles.at(particle_id).pos[id_dir] 
                      + particles.at(particle_id).vel[id_dir]*dt;
    
  }



  std::cout << "DB: " << new_pos[0] << " " << new_pos[1] << " " << new_pos[2] << std::endl;
  std::cout << "\n";

//////      // =======   Point 2)   =====================
//////      // ===  Check if I'm still in the cell  =====
//////
//////      x_is_in = (r_end[0] < p_cell->XYZcorners[1]) && (r_end[0] > p_cell->XYZcorners[0]);
//////      y_is_in = (r_end[1] < p_cell->XYZcorners[3]) && (r_end[1] > p_cell->XYZcorners[2]);
//////      z_is_in = (r_end[2] < p_cell->XYZcorners[5]) && (r_end[2] > p_cell->XYZcorners[4]);
//////
//////      if( x_is_in && y_is_in && z_is_in  ) {
//////        // adjourn particle position, then switch to the next particle
//////        p_part->pos[0] = r_end[0];
//////        continue;
//////      }
//////
//////      // =======   Point 3)   =====================
//////      // ====  If I'm out of the cell..   =========
//////      // !!!!!!!!!!!   THIS IS GOING TO WORK ONLY FOR 1D CASE   !!!!!!!!!!!!!!!!
//////      // !!!!!!!!!!!   3.1) process y and z with the MODULUS function
//////      // y_new = y_bottom + (y - y_bottom) % l_side
//////      // #include <math.h>;  then use fmod(x, y)  === x % y for doubles
//////
//////      // y AND z ARE SYMMETRY AND I'M IN 1D
//////      if( !y_is_in ) {
//////        r_end[1] = p_cell->XYZcorners[2] + fmod(r_end[1] - p_cell->XYZcorners[2], p_cell->get_side(1));
//////      }
//////
//////      if( !z_is_in ) {
//////        r_end[2] = p_cell->XYZcorners[4] + fmod(r_end[2] - p_cell->XYZcorners[4], p_cell->get_side(2));
//////      }
//////
//////      // x DISPLACEMENT MAY LEAD TO JUST TRASLATION OR REFLECTION OR.. ELSE
//////      if( !x_is_in) { // neighboring cell? Reflecting surface?
//////
//////        if( r_end[0] > p_cell->XYZcorners[1]) {        // Exited from face at X2
//////
//////          // What kind of face is it?
//////
//////        } else if( r_end[0] < p_cell->XYZcorners[0]) { // Exited from face at X1
//////
//////        }
//////        // [...]
//////
//////        // If the particle has exited, REMOVE IT FROM THE CELL AND ADD IT TO THE 
//////        // NEXT CELL
//////      }


////  // x direction
////  new_pos[0] = particles.at(particle_id).pos[0] + particles.at(particle_id).vel[0]*dt;
////
////  // y direction ( CYCLIC BCS!!!!!!! )
////  new_pos[1] = particles.at(particle_id).pos[1] + particles.at(particle_id).vel[1]*dt;
////
////  // z direction ( CYCLIC BCS!!!!!!! )
////  new_pos[2] = particles.at(particle_id).pos[2] + particles.at(particle_id).vel[2]*dt;

  return;
}

