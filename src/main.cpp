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
  solver Slvr(&Msh);
  Slvr.initialize();
  Slvr.seed_particles();

  // 4) Let's make some steps..
  Exptr.plot_particles_PNG("../output/provaoutput000.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput001.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput002.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput003.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput004.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput005.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput006.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput007.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput008.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput009.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput010.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput011.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput012.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput013.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput014.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput015.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput016.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput017.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput017.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput018.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput019.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput020.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput021.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput022.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput023.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput024.png");
  Slvr.translation_step();
  Exptr.plot_particles_PNG("../output/provaoutput025.png");

  Exptr.export_partpercell_VTK("../output/VTK_partpercell.vtk"); // for debugging reasons

  return 0;
}
