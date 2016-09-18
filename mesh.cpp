#include "mesh.h"

void mesh::set_n_cells(int nn) 
{
  this->n_cells = nn;
}

//------------------------------------------------------

int mesh::get_n_cells()
{
  return this->n_cells;
}

//------------------------------------------------------

void mesh::set_domain_box(double x1, double x2, double y1, double y2, double z1, double z2)
{
  // Set the limits of the outer box
  this->x_min = x1;
  this->x_max = x2;
  this->y_min = y1;
  this->y_max = y2;
  this->z_min = z1;
  this->z_max = z2;
}

//------------------------------------------------------

void mesh::create()
{
  std::cout << "Creating cells...\n";

  // Initialize "cells" vector
  cells.resize(get_n_cells());

  // Creates cells with some law.. Here it creates them on a straight line
  cell* p_cell_now;  // Pointer to cells

  for(size_t ii = 0; ii < get_n_cells(); ++ii) {
    p_cell_now = &cells.at(ii);   // Set pointer to current cell (I want to fill it!)
    // Setting X of corners
    p_cell_now->XYZcorners[0] = x_min + (ii) * (x_max - x_min)/get_n_cells();
    p_cell_now->XYZcorners[1] = x_min + (ii + 1) * (x_max - x_min)/get_n_cells();
    std::cout << "DB: p_cell_now->XYZcorners[0]: " << p_cell_now->XYZcorners[0] << "\n";
    std::cout << "DB: p_cell_now->XYZcorners[1]: " << p_cell_now->XYZcorners[1] << "\n\n";
    // Setting Y of corners
    p_cell_now->XYZcorners[2] = 0.;
    p_cell_now->XYZcorners[3] = 1.;
    // Setting Z of corners
    p_cell_now->XYZcorners[4] = -0.5;
    p_cell_now->XYZcorners[5] =  0.5;

  }

}
