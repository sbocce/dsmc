#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>

#include "particle.h"

class cell {
  public:
//    cell(){};
//    ~cell(){};

    double XYZcorners[6];                    // <<<<<---- X1 X2 Y1 Y2 Z1 Z2
    std::vector< int > neighbors;            // <<<<<---------------  !! Important! Xneighbors, Yneighbors, Zneighbors
    std::vector< particle > particles;

    // Geometry
    void   compute_sides();
    void   compute_volume();
    double get_side(size_t side_id);
    double get_volume();

    // BCs
    void   set_face_type(size_t face_id, char face_type);
    char   get_face_type(size_t face_id);

    // Utilities
    void   set_id(size_t cell_id);
    size_t get_id();
    void   remove_particle(size_t particle_id);

  private:
    double volume;
    double len_sides[3];
    size_t id;                              // <<<<<<<------------------  FARLO CON IL COSTRUTTORE

    char   face_type[6];   // Stores type of face for cubical cell. 
                           // o: open - p: periodic - a: axisimmetric - w: wall
                           // Order: x1, x2, y1, y2, z1, z2
                           
};

#endif /* CELL_H */
