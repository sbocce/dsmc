#ifndef PARTICLE_H
#define PARTICLE_H

class particle {
  public:
    double vel[3];
    double pos[3];

    void advect(double dt, double new_pos[]);
};

#endif /* PARTICLE_H*/
