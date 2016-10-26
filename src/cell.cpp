#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <string.h>
#include <math.h>

#include "cell.h"
#include "constants.h"

// --------------------------------------------
cell::cell() // constructor
{
  // Initializes all the faces of the cell to 'n', that is 'neighbor'.
  // The mesh class then can change some of them, to impose BCs such as walls.
  face_type[0] = 'n';
  face_type[1] = 'n';
  face_type[2] = 'n';
  face_type[3] = 'n';
  face_type[4] = 'n';
  face_type[5] = 'n';
}

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

void cell::set_face_type(size_t face_id, char face_type) 
{
  this->face_type[face_id] = face_type;
}

// --------------------------------------------

void cell::set_face_T(size_t face_id, double T) 
{
  this->face_T[face_id] = T;
}

// --------------------------------------------

void cell::set_face_a(size_t face_id, double a) 
{
  this->face_a[face_id] = a;
}
// --------------------------------------------

char cell::get_face_type(size_t face_id)
{
  return this->face_type[face_id];
}

// --------------------------------------------

double cell::get_face_T(size_t face_id)
{
  return this->face_T[face_id];
}

// --------------------------------------------

double cell::get_face_a(size_t face_id)
{
  return this->face_a[face_id];
}

// --------------------------------------------

void cell::add_particle(particle* p_part)
{
  // Adds the particle pointed by p_part to the current cell.
  // I can use this function to transfer cells among neighbors.. 
  // Or I could use it to implement a source somewhere!

  // 1) create a particle object
  particle part_now;

  // 2) fill it using the function particle::init_from_pointer() 
  part_now.init_from_pointer(p_part);

  // 3) push_back into the particles vector
  particles.push_back(part_now);
}

// --------------------------------------------

void cell::pop_particle(size_t particle_id)
{
  // Pops a particle off the cell
  particles.erase(particles.begin() + particle_id);
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
  //                            given by temperature and accommodation coefficient 
  // --------------------------------------------------------------------------

  bool      particle_crossed_face_A, particle_crossed_face_B; // working variables
  size_t    side_1, side_2, id_face; // working variables
  char      f_type_now;
  double    new_u_mod, alpha_rand, beta_rand;      // working variables
  double    new_direct; // double since it will multiply doubles
  particle* p_part = &(particles.at(particle_id));

  // ------  1D case  ------
  // It is simplified!
  // 1) I compute the adjourned position
  // 2) If the particle exits from the Y or Z faces, I use the modulus function to
  //    implement periodicity
  // 3) If the particle exits from the X face I check which face was it and then 
  //    treat it accordingly
  // 
  if( !strcmp(sol_type, "1D")) {

    p_part->pos[0] = p_part->pos[0] + p_part->vel[0]*dt;
    p_part->pos[1] = p_part->pos[1] + p_part->vel[1]*dt;
    p_part->pos[2] = p_part->pos[2] + p_part->vel[2]*dt;

    // Apply module function if particle exited from Y cells or Z cells

    // --- Y direction ---
    particle_crossed_face_A = (p_part->pos[1] < XYZcorners[2]);
    particle_crossed_face_B = (p_part->pos[1] > XYZcorners[3]);
    if(particle_crossed_face_B) {
      p_part->pos[1] = XYZcorners[2] + fmod(p_part->pos[1] - XYZcorners[3], get_side(1));
    } else if(particle_crossed_face_A) {
      p_part->pos[1] = XYZcorners[3] - fmod(XYZcorners[2] - p_part->pos[1], get_side(1));
    }

    // --- Z direction ---
    particle_crossed_face_A = (p_part->pos[2] < XYZcorners[4]);
    particle_crossed_face_B = (p_part->pos[2] > XYZcorners[5]);
    if(particle_crossed_face_B) {
      p_part->pos[2] = XYZcorners[4] + fmod(p_part->pos[2] - XYZcorners[5], get_side(2));
    } else if(particle_crossed_face_A) {
      p_part->pos[2] = XYZcorners[5] - fmod(XYZcorners[4] - p_part->pos[2], get_side(2));
    }

    // --- X direction ---
    particle_crossed_face_A = (p_part->pos[0] < XYZcorners[0]);
    particle_crossed_face_B = (p_part->pos[0] > XYZcorners[1]);
    if(particle_crossed_face_B || particle_crossed_face_A) { // Some face was crossed
      // find which one was crossed
//      (particle_crossed_face_A)? (id_face = 0) : (id_face = 1); // ternary operator..
      if(particle_crossed_face_A) {
        id_face    = 0;
        new_direct = 1; 
      } else {
        id_face    = 1;
        new_direct = -1;
      }
      f_type_now = get_face_type(id_face); // get face type

      // treat accordingly to the face type
      if(f_type_now == 'n') {// <<---------------------------- NEIGHBOR-TYPE face

        // add to X neighbor
        neighbors[0][id_face]->add_particle(p_part);

        // and remove it from the local cell
        pop_particle(particle_id);

      } else if(f_type_now == 'w') { // <<-------------------- WALL-TYPE face
        // Particles hitting the wall are assigned the position of the wall and a new velocity,
        // that is the opposite of the previous one if the accomodation coefficient is alpha = 0 or 
        // random and according to the wall temperature if alpha \neq 0

        // PARTICLE NEW POSITION
        p_part->pos[0] = XYZcorners[id_face];  // particle is stopped at the wall position. It will
                                           // move again later
        // PARTICLE NEW VELOCITY (accommodation factor = 1 for now..)
        new_u_mod  = sqrt(3*kB*get_face_T(id_face)/p_part->get_mass());
        alpha_rand = pi*( rand()/double(RAND_MAX) );
        beta_rand  = 2*pi*( rand()/double(RAND_MAX) ); // 2*pi in the YZ plane! 
        p_part->vel[0] = new_direct*new_u_mod*sin(alpha_rand);
        p_part->vel[1] =          1*new_u_mod*cos(alpha_rand)*sin(beta_rand);
        p_part->vel[2] =          1*new_u_mod*cos(alpha_rand)*cos(beta_rand);

      }
    }

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

  return;
}

