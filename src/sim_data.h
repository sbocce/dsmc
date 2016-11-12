#ifndef SIM_DATA_H
#define SIM_DATA_H

#include <vector>
#include <string>

class sim_data {
  public:
    sim_data(std::string s_file_input);
    ~sim_data(){};

    // Functions for reading input file
    std::string parseline(std::string line);
    void read_input_file();

    // Simulation parameters
    double      get_dt(); // returns timestep
    const char* get_sol_type(); // returns the solution type

    // Species parameters
    double get_species_mass(size_t s_id);
    double get_species_diam(size_t s_id);
    double get_species_omega(size_t s_id);

    void   initialize(); // fills internal variables

  private:
    
    std::string s_file_input; // Input file

    // Parameters of the simulation
    double dt;   // value of timestep
    double Fnum; // number of molecules simulated by each DSMC particle

    const char* sol_type; // 1D or 2D or 2D axisimmetric or 3D

    // Here are molecular parameters. Not all of them are necessarily filled
    // up: depends on which collisional model is choosen for example.
    std::vector<double> species_mass;     // particle mass
    std::vector<double> species_diameter; // reference diameter
    std::vector<double> species_omega;    // VHS omega parameter
};

#endif /* SIM_DATA_H */
