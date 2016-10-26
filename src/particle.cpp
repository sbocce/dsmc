#include "particle.h"


// ---------------------------------------------------

void particle::advect(double dt, double new_pos[])
{
  new_pos[0] = pos[0] + vel[0]*dt;
  new_pos[1] = pos[1] + vel[1]*dt;
  new_pos[2] = pos[2] + vel[2]*dt;
}

// ---------------------------------------------------

void particle::set_mass(double mass)
{
  this->m = mass;
}

// ---------------------------------------------------

double particle::get_mass()
{
  return this->m;
}

// ---------------------------------------------------

void particle::init_from_pointer(particle* p_part)
{
  // Given a pointer to a particle, this function copies the values
  // from that particle to the local one.
  // REMEMBER TO UPDATE THIS FUNCTION IF NEW FEATURES SUCH AS ROTATIONAL
  // OR VIBRATIONAL STATES OR WHATEVER IS ADDED!!!!

  this->set_mass(p_part->get_mass());

  this->pos[0] = p_part->pos[0];
  this->pos[1] = p_part->pos[1];
  this->pos[2] = p_part->pos[2];

  this->vel[0] = p_part->vel[0];
  this->vel[1] = p_part->vel[1];
  this->vel[2] = p_part->vel[2];

}
