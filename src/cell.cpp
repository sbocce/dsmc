#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <string.h>
#include <math.h>

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

void cell::advect_particle(size_t particle_id, double dt, const char* sol_type)
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
  //     2.2.1) is it a periodicity direction? 1D or 2D simulations for example..
  //            
  //       2.2.1.1) yes -> then just apply modulus function
  //       2.2.1.2) no -> ..ok... 
  // 
  //         2.2.1.2.1) find out which face was crossed (first or second)
  //         2.2.1.2.2) act accordingly:
  //            - Free face:    move particle to the neighboring cell
  //            - Outflow face: just remove the particle
  //            - Solid wall:   re-emit the particle inside the cell with a velocity 
  //                            given by temperature and accommodation factor
  // --------------------------------------------------------------------------

  double new_pos[3];
  bool   particle_crossed_face_A, particle_crossed_face_B; // working variables
  size_t side_1, side_2, face_id; // working variables
  char   f_type_now;

  // ------  1D case  ------
  // It is simplified!
  // 1) I compute the adjourned position
  // 2) If the particle exits from the Y or Z faces, I use the modulus function to
  //    implement periodicity
  // 3) If the particle exits from the X face I check which face was it and then 
  //    treat it accordingly
  // 
  if( !strcmp(sol_type, "1D")) {

    new_pos[0] =   particles.at(particle_id).pos[0] + particles.at(particle_id).vel[0]*dt;
    new_pos[1] =   particles.at(particle_id).pos[1] + particles.at(particle_id).vel[1]*dt;
    new_pos[2] =   particles.at(particle_id).pos[2] + particles.at(particle_id).vel[2]*dt;

    // Apply module function if particle exited from Y cells or Z cells

    // --- Y direction ---
    particle_crossed_face_A = (new_pos[1] < XYZcorners[2]);
    particle_crossed_face_B = (new_pos[1] > XYZcorners[3]);
    if(particle_crossed_face_B) {
      new_pos[1] = XYZcorners[2] + fmod(new_pos[1] - XYZcorners[3], get_side(1));
    } else if(particle_crossed_face_A) {
      new_pos[1] = XYZcorners[3] - fmod(XYZcorners[2] - new_pos[1], get_side(1));
    }

    // --- Z direction ---
    particle_crossed_face_A = (new_pos[2] < XYZcorners[4]);
    particle_crossed_face_B = (new_pos[2] > XYZcorners[5]);
    if(particle_crossed_face_B) {
      new_pos[2] = XYZcorners[4] + fmod(new_pos[2] - XYZcorners[5], get_side(2));
    } else if(particle_crossed_face_A) {
      new_pos[2] = XYZcorners[5] - fmod(XYZcorners[4] - new_pos[2], get_side(2));
    }

    // --- X direction ---
    particle_crossed_face_A = (new_pos[0] < XYZcorners[0]);
    particle_crossed_face_B = (new_pos[0] > XYZcorners[1]);
    if(particle_crossed_face_B || particle_crossed_face_A) { // Some face was crossed
      // find which one was crossed
      (particle_crossed_face_A)? (id_face = 0) : (id_face = 1); // ternary operator..
      f_type_now = get_face_type(id_face); // get face type
      // treat accordingly to the face type
      if(strcmp()) {// open face: just let it go FOR NOW <<<<------------------------------------ FOR NOW
      
      } else if(strcmp()) { // reflective face 

      }
    }

    // FOR NOW I KEEP IT FREE!!!!

    // Adjourn particle position
    particles.at(particle_id).pos[0] = new_pos[0];
    particles.at(particle_id).pos[1] = new_pos[1];
    particles.at(particle_id).pos[2] = new_pos[2];

  } else {
    std::cout << "Solution for domain type '" << sol_type << "' not implemented yet!\n";  
  }


  //// -----------------------------------------
  //// GENERIC CASE: 3D (.....embrionale..)
  //// -----------------------------------------
  //for(size_t id_dir = 0; id_dir < 3; ++id_dir) { // for each direction.. x, y, z
 
  //  // try to update position 
  //  new_pos[id_dir] =   particles.at(particle_id).pos[id_dir] 
  //                    + particles.at(particle_id).vel[id_dir]*dt;

  //  // Did the particle exit the cell? Check on the vector XYZcorners
  //  side_1 = 2*id_dir;
  //  side_2 = 2*id_dir + 1;
  //  particle_crossed_wall_1 = (new_pos[id_dir] < XYZcorners[side_1]);
  //  particle_crossed_wall_2 = (new_pos[id_dir] > XYZcorners[side_2]);

  //  if( particle_crossed_wall_1 || particle_crossed_wall_2 ) { // hey, it crossed some wall!

  //    std::cout << "Some particle crossed the borders!" << std::endl;

  //    // Is it a special direction?
  //    if( 
  //        // 1D solution and I'm processing y or z axis
  //           ( !strcmp(sol_type, "1D") && ((id_dir == 1) || (id_dir == 2)) )
  //        // .. or 2D solution and I'm processing z axis
  //        || ( !strcmp(sol_type, "2D") && id_dir == 2)          
  //      ) {

  //      std::cout << "Solution is 1D\n";

  //      new_pos[id_dir] =  XYZcorners[side_1] 
  //                       + fmod(new_pos[id_dir] - XYZcorners[side_2], get_side(id_dir));
  //      continue;

  //    } else {
  //      std::cout << "Some unrecognized geometry was selected.." << std::endl;
  //    }
  //  }
  // 
  //}



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

