#include <iostream>

#include "mesh.h"
#include "exporter.h"
#include "solver.h"


int main()
{
  // 1) Create mesh
  mesh Msh;
  Msh.set_n_cells(5);
  Msh.set_domain_box(-1.5, 5, 0, 1, -0.5, 0.5);   // Set outer compuational domain
  Msh.create();

  // 2) Create exporter object
  exporter Exptr(&Msh);
  Exptr.export_mesh_VTK("VTK_mesh.vtk");  

  // 3) Create solver object
  solver Slvr(&Msh);
  Slvr.initialize();
  Slvr.seed_particles();

  // 4) Let's make some steps..
  Slvr.translation_step();
  Exptr.export_partpercell_VTK("VTK_partpercell.vtk"); // for debugging reasons

  return 0;
}
