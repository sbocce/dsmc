#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()

//#include "particle.h"
#include "cell.h"
#include "mesh.h"


int main()
{
  // 1) Create mesh
  mesh Msh;
  Msh.set_n_cells(5);
  Msh.set_domain_box(-1.5, 5, 0, 1, -0.5, 0.5);   // Set outer compuational domain
  Msh.create();

  std::cout << "Num celle: " << Msh.get_n_cells() << std::endl;

  for(size_t ii = 0; ii < Msh.get_n_cells() ; ++ii)
  {
    std::cout << Msh.cells.at(ii).XYZcorners[0] << std::endl;
    std::cout << Msh.cells.at(ii).XYZcorners[1] << std::endl << std::endl;
  }

  // 2) do the rest..

//  particle part_now; // A particle to be copied..
//
//
////    // ------- Fill it with a random number of particles -------
////
////    // for ii = 1 : n_particles
////      // Create a particle at random position in the cell
////      double rand_now1 = rand() / double(RAND_MAX);
////      double rand_now2 = rand() / double(RAND_MAX);
////      double rand_now3 = rand() / double(RAND_MAX);
////      part_now.pos[0] = p_cell_now->XYZcorners[0] + \
////                        rand_now1*(p_cell_now->XYZcorners[1] - p_cell_now->XYZcorners[0]);  // x
////      part_now.pos[1] = p_cell_now->XYZcorners[2] + \
////                        rand_now2*(p_cell_now->XYZcorners[3] - p_cell_now->XYZcorners[2]);  // y
////      part_now.pos[2] = p_cell_now->XYZcorners[4] + \
////                        rand_now3*(p_cell_now->XYZcorners[5] - p_cell_now->XYZcorners[4]);  // z
////
////      // Give to the particle a random velocity
//////      double rand_now4 = rand() / double(RAND_MAX);
//////      double rand_now5 = rand() / double(RAND_MAX);
//////      double rand_now6 = rand() / double(RAND_MAX);
//////      part_now.vel[0] = 
////     
////      // Push the particle into the cell 
////      p_cell_now->particles.push_back(part_now);

  return 0;
}
