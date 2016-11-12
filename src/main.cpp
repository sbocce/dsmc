#include <iostream>
#include <stdlib.h>     /* system, exit, EXIT_FAILURE */

//REMOVE IT
#include <cmath> // REMOVE ME!!!
//REMOVE IT

#include "sim_data.h"
#include "mesh.h"
#include "exporter.h"
#include "collider.h"
#include "solver.h"

#include "lodepng.h"

int main(int argc, char *argv[])
{
  if(argc < 2) { std::cerr << "Provide an input file! ABORTING!\n"; exit(1); }

  // 0) Simulation data
  sim_data Data(argv[1]);  // in the constructor reads input file etc

  // 1) Create mesh
  mesh Msh(&Data);
  Msh.set_n_cells(5);
  Msh.set_domain_box(-1.5, 5, 0, 1, -1.5, 0.5);   // Set outer compuational domain
  Msh.create();
  Msh.impose_BCs();

  // 2) Create exporter object
  exporter Exptr(&Msh);
  Exptr.export_mesh_VTK("./output/VTK_mesh.vtk");  

  // 3) Create collider object
  collider Clldr(&Data, &Msh);

  // 4) Create solver object
  solver Slvr(&Data, &Msh, &Exptr);
  Slvr.seed_particles();

  // 5) Let's make some steps..
  Slvr.compute_n_steps(30);

  // 6) Some exporting
  Exptr.export_partpercell_VTK("./output/VTK_partpercell.vtk"); // for debugging reasons

  return 0;
}
