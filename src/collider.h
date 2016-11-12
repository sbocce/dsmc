#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>
#include <vector>

#include "sim_data.h"
#include "particle.h"
#include "mesh.h"

class collider {
  public:
    collider(sim_data* p_dat, mesh* p_msh){};
    ~collider(){};
};

#endif /* COLLIDER_H */
