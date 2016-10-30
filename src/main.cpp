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
  Msh.set_domain_box(-1.5, 5, 0, 1, -1.5, 0.5);   // Set outer compuational domain
  Msh.create();
  Msh.impose_BCs();

  // 2) Create exporter object
  exporter Exptr(&Msh);
  Exptr.export_mesh_VTK("../output/VTK_mesh.vtk");  

  // 3) Create solver object
  solver Slvr(&Msh, &Exptr);
  Slvr.initialize();
  Slvr.seed_particles();

  // 4) Let's make some steps..
  Slvr.compute_n_steps(10);

  // 5) Some exporting
  Exptr.export_partpercell_VTK("../output/VTK_partpercell.vtk"); // for debugging reasons

  return 0;
}
