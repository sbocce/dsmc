#include "stat_tools.h"

double sample_uniform_dist(double x1, double x2)
{
  // get a random value from zero to one
  double randval = rand()/double(RAND_MAX);

  // scale it to be among the extremes and then return
  return x1 + randval*(x2 - x1);
}
