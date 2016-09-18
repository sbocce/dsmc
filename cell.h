#ifndef CELL_H
#define CELL_H

#include <vector>

#include "particle.h"

class cell {
  public:
    double XYZcorners[6];
    std::vector< int > neighbors;            // <<<<<---------------  !! Important!
    std::vector< particle > particles;

    void compute_sides();
    void compute_volume();
    void get_sides();
    void get_volume();

  private:
    double volume;
    double len_sides[3];
};

#endif /* CELL_H */
