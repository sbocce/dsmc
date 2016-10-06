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
