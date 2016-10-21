#include <iostream>
#include <fstream>
#include <sstream>

#include "exporter.h"

exporter::exporter(mesh* p_msh) : p_mesh(p_msh) { }

// ---------------------------------------------

void exporter::export_mesh_VTK(const char* filename)
{
  cell* p_cell_now; // pointer to cell
  double x1now, x2now, x3now, x4now;
  double y1now, y2now, y3now, y4now;

  size_t n_cells = p_mesh->get_n_cells();

  std::ofstream fileVTK;
  fileVTK.open(filename, std::ios::trunc); // open the file (destroy if exists)
  if (fileVTK.is_open() == 1) // file correctly initialized
  { 
    // writing VTK stuff
    fileVTK << "# vtk DataFile Version 2.0\n";
    fileVTK << "Generated by VTKer\n";
    fileVTK << "ASCII\n";
    fileVTK << "DATASET UNSTRUCTURED_GRID\n";
    fileVTK << "POINTS " << 4*n_cells << " float\n";
    for(int ii = 0; ii < n_cells; ii++)
    {
      p_cell_now = &(p_mesh->cells.at(ii));
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
    fileVTK.close();
  } 
  else { 
    std::cout << " There was an error opening file! In export_mesh_VTK()\n";
  }
}

// ---------------------------------------------

void exporter::export_partpercell_VTK(const char* filename)
{
  // 1) create a mesh file with a certain name, using the function export_mesh_VTK()
  export_mesh_VTK(filename);

  // 2) open this file again in append mode and add the required field (particles 
  // per cell in this case)
  std::ofstream fileVTK;
  fileVTK.open(filename, std::ios::app); // open the file (destroy if exists)

  size_t n_particles;

  // Write stuff
  fileVTK << "\n";
  fileVTK << "POINT_DATA " << 4*p_mesh->get_n_cells() << "\n";
  fileVTK << "SCALARS particles_per_cell float 1\n";
  fileVTK << "LOOKUP_TABLE default\n";
  for(size_t id_c=0; id_c<p_mesh->get_n_cells(); ++id_c)
  {
    n_particles = p_mesh->cells.at(id_c).particles.size();
    fileVTK << n_particles <<" "<< n_particles 
            <<" "<< n_particles <<" "<< n_particles <<"\n";
  }

  // Closing VTK file
  fileVTK.close();
} 
