#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>

#include "particle.h"

class cell {
  public:
//    cell(){};
//    ~cell(){};

    double XYZcorners[6];
    std::vector< int > neighbors;            // <<<<<---------------  !! Important!
    std::vector< particle > particles;

    void compute_sides();
    void compute_volume();
    void get_sides();
    void get_volume();
    void set_id(size_t cell_id);
    size_t get_id();

  private:
    double volume;
    double len_sides[3];
    size_t id;                              // <<<<<<<------------------  FARLO CON IL COSTRUTTORE
};

#endif /* CELL_H */
