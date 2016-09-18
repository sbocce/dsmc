#include <iostream>

#include "mesh.h"
#include "solver.h"


int main()
{
  // 1) Create mesh
  mesh Msh;
  Msh.set_n_cells(5);
  Msh.set_domain_box(-1.5, 5, 0, 1, -0.5, 0.5);   // Set outer compuational domain
  Msh.create();

  // Export mesh
  Msh.export_VTK();

  // 2) Create solver object
  solver Slvr(&Msh);
  Slvr.initialize();
  Slvr.seed_particles();

  Slvr.translation_step();



  return 0;
}
