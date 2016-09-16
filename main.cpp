#include <iostream>
#include <vector>


class particle {
  public:
    double vel[3];
    double pos[3];
};


class cell {
  public:
    double XYZcorners[6];
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

 
  cell* p_cell_now; // Pointer to cells

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
  }                      

  for(size_t ii = 0; ii < N_cells; ++ii) {
    std::cout << "X: " << cells_vec[ii].XYZcorners[0] << "   \n";
  }
                         

  std::cout << "Ciao! Celle: " << cells_vec.size() << "\n";
  return 0;
}
