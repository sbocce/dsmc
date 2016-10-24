#include <iostream>
#include <fstream>
#include <sstream>

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

  for(size_t ii = 0; ii < get_n_cells(); ++ii) {
    p_cell_now = &cells.at(ii);   // Set pointer to current cell (I want to fill it!)

    // Set cell ID
    p_cell_now->set_id(ii);

    // Setting X of corners
    p_cell_now->XYZcorners[0] = x_min + (ii) * (x_max - x_min)/get_n_cells();
    p_cell_now->XYZcorners[1] = x_min + (ii + 1) * (x_max - x_min)/get_n_cells();
    // Setting Y of corners
    p_cell_now->XYZcorners[2] = 0.;
    p_cell_now->XYZcorners[3] = 1.;
    // Setting Z of corners
    p_cell_now->XYZcorners[4] = -0.5;
    p_cell_now->XYZcorners[5] = 0.5;

    // Compute sides of each cell
    p_cell_now->compute_sides();
std::cout << " DBBB: side of cell: " << p_cell_now->get_side(0) << " " <<
                                        p_cell_now->get_side(1) << " " << 
                                        p_cell_now->get_side(2) << std::endl;
  }

}


