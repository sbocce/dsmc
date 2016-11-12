#ifndef PARTICLE_H
#define PARTICLE_H

class particle {
  public:
    particle(){};
    ~particle(){};

    double vel[3];
    double pos[3];

    int    species; // identifier the particle species

    void   advect(double dt, double new_pos[]);
    double compute_e_t(); // Computes and returns the translational energy of the 
                          // particle

    void   set_mass(double mass);
    double get_mass();

    void   init_from_pointer(particle* p_part); // initializes a particle copying 
                                                // properties from a pointer. Cool 
                                                // that this works!

  private:
    double m; // mass is given at the moment of particle creation
};

#endif /* PARTICLE_H*/
