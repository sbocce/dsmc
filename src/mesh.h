#ifndef MESH_H
#define MESH_H

#include <iostream>

#include "sim_data.h"
#include "cell.h"

class mesh {

  public:
    mesh(sim_data* p_dat);
    ~mesh(){};

    void set_n_cells(int nn);
    int  get_n_cells();
    void set_domain_box(double x1, double x2, double y1, double y2, double z1, double z2);
    void get_domain_box(double& x1, double& x2, double& y1, double& y2, double& z1, double& z2);
    void impose_BCs();
    void create();
  
    std::vector< cell > cells;
    double x_min, x_max, y_min, y_max, z_min, z_max; // Limits of computational domain

  private:
    sim_data* p_data;
    int n_cells;
    
};
#endif /* MESH_H*/
