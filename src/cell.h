#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <vector>

#include "particle.h"

class cell {
  public:
    cell();
    ~cell(){};

    double XYZcorners[6];                    // <<<<<---- X1 X2 Y1 Y2 Z1 Z2
    std::vector< std::vector<cell*> > neighbors;            // <<<<<---------------  !! Important! Xneighbors, Yneighbors, Zneighbors
    std::vector< particle > particles;

    // Geometry
    void   compute_sides();
    void   compute_volume();
    double get_side(size_t side_id);
    double get_volume();

    // Cell faces (and BCs)
    void   set_face_type(size_t face_id, char face_type);
    void   set_face_T(size_t face_id, double T);   // temperature
    void   set_face_a(size_t face_id, double a);   // accommodation coefficien 

    char   get_face_type(size_t face_id);
    double get_face_T(size_t face_id);     // temperature
    double get_face_a(size_t face_id);     // accommodation coefficient 

    // Utilities
    void   set_id(size_t cell_id);
    size_t get_id();
    void   advect_particle(size_t particle_id, double dt, const char* sol_type);
    void   remove_particle(size_t particle_id);

  private:
    double volume;
    double len_sides[3];
    size_t id;                              // <<<<<<<------------------  FARLO CON IL COSTRUTTORE

    // The following variables are about the cell faces.
    // Faces are ordered as: x_min, x_max, y_min, y_max, z_min, z_max.
    // Vectors shown here are inizialized to some standard value in the constructor
    //
    // face_type -------> stores the type of face. May be of type:
    //                    o: open - p: periodic - a: axisimmetric - w: wall - n: neighboring cell
    //
    // face_T ----------> stores the temperature of the faces. It has meaning only for faces 
    //                    that are walls.
    //
    // face_a ----------> stores the accommodation coefficient. Has meaning only for faces that 
    //                    are walls.

    char   face_type[6];
    char   face_T[6];
    char   face_a[6];
};

#endif /* CELL_H */
