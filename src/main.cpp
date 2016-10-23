#include <iostream>

//REMOVE IT
#include <cmath> // REMOVE ME!!!
//REMOVE IT

#include "mesh.h"
#include "exporter.h"
#include "solver.h"

#include "lodepng.h"

int main(int argc, char *argv[])
{
  // 1) Create mesh
  mesh Msh;
  Msh.set_n_cells(5);
  Msh.set_domain_box(-1.5, 5, 0, 1, -0.5, 0.5);   // Set outer compuational domain
  Msh.create();

  // 2) Create exporter object
  exporter Exptr(&Msh);
  Exptr.export_mesh_VTK("../output/VTK_mesh.vtk");  

  // 3) Create solver object
  solver Slvr(&Msh);
  Slvr.initialize();
  Slvr.seed_particles();

  // 4) Let's make some steps..
  Slvr.translation_step();
  std::cout << "-----------------------------------------\n";
  Slvr.translation_step();
  
  Exptr.export_partpercell_VTK("../output/VTK_partpercell.vtk"); // for debugging reasons
  Exptr.plot_particles_PNG("../output/provaoutput.png");

  return 0;
}
