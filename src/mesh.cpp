#include <iostream>
#include <fstream>
#include <sstream>

#include "mesh.h"

mesh::mesh(sim_data* p_dat) : p_data(p_dat) { }

//------------------------------------------------------

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

void mesh::get_domain_box(double& x1, double& x2, double& y1, double& y2, double& z1, double& z2)
{
  // Set the limits of the outer box
  x1 = this->x_min;
  x2 = this->x_max;
  y1 = this->y_min;
  y2 = this->y_max;
  z1 = this->z_min;
  z2 = this->z_max;
}

//------------------------------------------------------

void mesh::create()
{
  std::cout << "Creating cells...\n";

  // Initialize "cells" vector
  cells.resize(get_n_cells());

  // Creates cells with some law.. Here it creates them on a straight line
  cell* p_cell_now;  // Pointer to cells

  for(size_t id_c = 0; id_c < get_n_cells(); ++id_c) {
    p_cell_now = &cells.at(id_c);   // Set pointer to current cell (I want to fill it!)

    // Set cell ID
    p_cell_now->set_id(id_c);

    // Setting X of corners
    p_cell_now->XYZcorners[0] = x_min + (id_c) * (x_max - x_min)/get_n_cells();
    p_cell_now->XYZcorners[1] = x_min + (id_c + 1) * (x_max - x_min)/get_n_cells();
    // Setting Y of corners
    p_cell_now->XYZcorners[2] = y_min;  // ONLY OK FOR 1D SIMULATIONS!
    p_cell_now->XYZcorners[3] = y_max;  // ONLY OK FOR 1D SIMULATIONS!
    // Setting Z of corners
    p_cell_now->XYZcorners[4] = z_min;  // ONLY OK FOR 1D SIMULATIONS!
    p_cell_now->XYZcorners[5] = z_max;  // ONLY OK FOR 1D SIMULATIONS!

    // Compute sides of each cell
    p_cell_now->compute_sides();

    // Set neighbors: assign to each cell (except the first and the last), their neighbors.
    // The neighbors matrix is made of three vectors: neighbors[0], [1], [2]
    // each of them contains POINTERS to the neighboring cells.

    // First of all resize:
    p_cell_now->neighbors.resize(3);       // X, Y and Z neighbors
    p_cell_now->neighbors.at(0).resize(2); // on X we have 2 neighbors
    p_cell_now->neighbors.at(1).resize(2); // on Y we have 2 neighbors
    p_cell_now->neighbors.at(2).resize(2); // on Z also, we have 2 neighbors

    if(id_c > 0) {
      p_cell_now->neighbors[0].at(0) = &(cells.at(id_c-1)); // X, left neighbor
    }
    if(id_c < get_n_cells() - 1) {
      p_cell_now->neighbors[0].at(1) = &(cells.at(id_c+1)); // X, right neighbor
    }
    
  }

}

//------------------------------------------------------

void mesh::impose_BCs()
{
  // This function somehow knows which BCs to impose. For now (1D case) I hard-code it.

  // First cell
  cells.at(0).set_face_type(0, 'w');
  cells.at(0).set_face_T(0, 1000);
  cells.at(0).set_face_a(0, 0);
  // Last cell
  cells.at(get_n_cells()-1).set_face_type(1, 'w');
  cells.at(get_n_cells()-1).set_face_T(1, 273.15);
  cells.at(get_n_cells()-1).set_face_a(1, 1);
}
