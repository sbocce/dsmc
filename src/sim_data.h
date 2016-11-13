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
    void file_to_string(std::string s_file, std::vector<std::string>& linesVect);

    void read_input_file();

    // Simulation parameters
    double      get_dt(); // returns timestep
    std::string get_sol_type(); // returns the solution type

    // Species parameters
    size_t get_n_species();
    double get_species_name(size_t s_id);
    double get_species_mass(size_t s_id);
    double get_species_charge(size_t s_id);

    void   initialize(); // fills internal variables

    // General purpose
    bool get_png_flag();

  private:
    
    std::string s_file_input; // Input file

    // Parameters of the simulation
    double dt;   // value of timestep
    double Fnum; // number of molecules simulated by each DSMC particle

    std::string sol_type; // 1D or 2D or 2D axisimmetric or 3D

    // Variables for species
    std::string              species_file;    // name of file for species props
    size_t                   n_species;       // number of species
    std::vector<std::string> species_name;    // name of species
    std::vector<double>      species_mass;    // species molecular mass [kg]
    std::vector<double>      species_charge;  // species charge [q_el]

    std::string              collisions_file;    // name of file for species props

    // General variables
    bool png_flag;
};

#endif /* SIM_DATA_H */
