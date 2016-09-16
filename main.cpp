#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()

class particle {
  public:
    double vel[3];
    double pos[3];
};


class cell {
  public:
    double XYZcorners[6];
    std::vector< int > neighbors;            // <<<<<---------------  !! Important!
    std::vector< particle > particles;

    void compute_sides();
    void compute_volume();
    void get_sides();
    void get_volume();

  private:
    double volume;
    double len_sides[3];
};



int main()
{
  // ============  Creating cells  ===============
  int N_cells = 3;
  std::vector< cell > cells_vec(N_cells);

  double x_min = 0.;
  double x_max = 8.;

 
  cell* p_cell_now;  // Pointer to cells
  particle part_now; // A particle to be copied..

  for(size_t ii = 0; ii < N_cells; ++ii) {
    p_cell_now = &cells_vec.at(ii);   // Set pointer to current cell
    // Setting X of corners
    p_cell_now->XYZcorners[0] = x_min + (ii) * (x_max - x_min)/N_cells;
    p_cell_now->XYZcorners[1] = x_min + (ii + 1) * (x_max - x_min)/N_cells;
    std::cout << "DB: p_cell_now->XYZcorners[0]: " << p_cell_now->XYZcorners[0] << "\n";
    std::cout << "DB: p_cell_now->XYZcorners[1]: " << p_cell_now->XYZcorners[1] << "\n\n";
    // Setting Y of corners
    p_cell_now->XYZcorners[2] = 0.;  
    p_cell_now->XYZcorners[3] = 1.;
    // Setting Z of corners
    p_cell_now->XYZcorners[4] = -0.5;
    p_cell_now->XYZcorners[5] =  0.5;


    // ------- Fill it with a random number of particles -------

    // for ii = 1 : n_particles
      // Create a particle at random position in the cell
      double rand_now1 = rand() / double(RAND_MAX);
      double rand_now2 = rand() / double(RAND_MAX);
      double rand_now3 = rand() / double(RAND_MAX);
      part_now.pos[0] = p_cell_now->XYZcorners[0] + \
                        rand_now1*(p_cell_now->XYZcorners[1] - p_cell_now->XYZcorners[0]);  // x
      part_now.pos[1] = p_cell_now->XYZcorners[2] + \
                        rand_now2*(p_cell_now->XYZcorners[3] - p_cell_now->XYZcorners[2]);  // y
      part_now.pos[2] = p_cell_now->XYZcorners[4] + \
                        rand_now3*(p_cell_now->XYZcorners[5] - p_cell_now->XYZcorners[4]);  // z

      // Give to the particle a random velocity
//      double rand_now4 = rand() / double(RAND_MAX);
//      double rand_now5 = rand() / double(RAND_MAX);
//      double rand_now6 = rand() / double(RAND_MAX);
//      part_now.vel[0] = 
     
      // Push the particle into the cell 
      p_cell_now->particles.push_back(part_now);
  }                      


  return 0;
}
