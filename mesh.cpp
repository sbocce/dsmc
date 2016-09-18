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
    p_cell_now->XYZcorners[5] =  0.5;

  }

}

//------------------------------------------------------

void mesh::export_VTK()
{
  std::cout << "Exporting mesh in legacy-VTK form:" << std::endl;

  cell* p_cell_now; // pointer to cell
  double x1now, x2now, x3now, x4now;
  double y1now, y2now, y3now, y4now;

  std::ofstream fileVTK;
  fileVTK.open("mesh.vtk", std::ios::trunc); // open the file (destroy if exists)
  if (fileVTK.is_open() == 1) // file correctly initialized
  { std::cout << " > Output file opened and ready for writing..\n"; }

  // writing VTK stuff
  fileVTK << "# vtk DataFile Version 2.0\n";
  fileVTK << "Generated by VTKer\n";
  fileVTK << "ASCII\n";
  fileVTK << "DATASET UNSTRUCTURED_GRID\n";
  fileVTK << "POINTS " << 4*n_cells << " float\n";
  for(int ii = 0; ii < n_cells; ii++)
  {
    p_cell_now = &cells.at(ii);
    x1now = p_cell_now->XYZcorners[0];
    x2now = p_cell_now->XYZcorners[1];
    x3now = p_cell_now->XYZcorners[1]; 
    x4now = p_cell_now->XYZcorners[0];

    y1now = p_cell_now->XYZcorners[2];
    y2now = p_cell_now->XYZcorners[2];
    y3now = p_cell_now->XYZcorners[3];
    y4now = p_cell_now->XYZcorners[3];
    
    fileVTK << x1now << " " << y1now << " 0   ";
    fileVTK << x2now << " " << y2now << " 0   ";
    fileVTK << x3now << " " << y3now << " 0   ";
    fileVTK << x4now << " " << y4now << " 0   ";
    fileVTK << "\n";
  }

  fileVTK << "\n";
  fileVTK << "CELLS " << n_cells << " " << 5*n_cells << "\n";
  for(int ii = 0; ii < n_cells; ii++)
  {
    fileVTK << "4 ";
    fileVTK << 0 + 4*ii << " ";
    fileVTK << 1 + 4*ii << " ";
    fileVTK << 2 + 4*ii << " ";
    fileVTK << 3 + 4*ii << " ";
    fileVTK << "\n";
  }

  fileVTK << "\n";
  fileVTK << "CELL_TYPES " << n_cells << "\n";
  for(int ii = 0; ii < n_cells; ii++)
  {
    fileVTK << "9\n";
  }

  // Closing VTK file
  std::cout << " > Writing done. Closing file.\n\n";
  fileVTK.close();
}
