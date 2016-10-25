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
