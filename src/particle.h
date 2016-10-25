#ifndef PARTICLE_H
#define PARTICLE_H

class particle {
  public:
    particle(){};
    ~particle(){};

    double vel[3];
    double pos[3];

    void   advect(double dt, double new_pos[]);
    double compute_e_t(); // Computes and returns the translational energy of the particle

    void   set_mass(double mass);
    double get_mass();

  private:
    double m; // mass is given at the moment of particle creation
};

#endif /* PARTICLE_H*/
