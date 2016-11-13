#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>     /* system, exit, EXIT_FAILURE */


#include "sim_data.h"


sim_data::sim_data(std::string s_file_input) : png_flag(0) // initialized to 0
{ 

std::cout << "                                               " << std::endl;  
std::cout << "         _                                     " << std::endl;         
std::cout << "        | |            ___  ___ __  __  ___    " << std::endl;  
std::cout << "        | |_  __    _ |   \\/ __|  \\/  |/ __|   " << std::endl; 
std::cout << "        | ' \\/ .`|/V V\\ |) \\__ \\ |\\/| | (__    " << std::endl; 
std::cout << "        |_||_\\__,|\\_._/___/|___/_|  |_|\\___|   " << std::endl; 
std::cout << "                                               " << std::endl;  
std::cout << "  > horsing around with DSMC <                 " << std::endl;  
std::cout << "                                               " << std::endl;  
std::cout << "                                               " << std::endl;  

  this->s_file_input = s_file_input;
  this->initialize();
}

// ---------------------------------------------

double sim_data::get_dt()
{
  return this->dt;
}

// ---------------------------------------------

std::string sim_data::get_sol_type()
{
  return this->sol_type;
}

// ---------------------------------------------

size_t sim_data::get_n_species()
{
  return this->n_species;
}

// ---------------------------------------------

bool sim_data::get_png_flag()
{
  return this->png_flag;
}

// ---------------------------------------------

std::string sim_data::parseline(std::string line)
{
  // Remove comments starting somewhere in the line
  for(size_t ii = 0; ii < line.length(); ++ii) {
    if(line[ii] == '#') { // then the rest is a comment, trim it!
      line = line.substr(0,ii);
    }
  }
  // Removing whitespaces in the beginning of the line
  while( line[0] == ' ' ) {
    line = line.substr(1, line.length());
  }
  // Removing whitespaces in the end of the line
  while( line[line.length()-1] == ' ' ) {
    line = line.substr(0, line.length()-1);
  }
  return line;
};

// ---------------------------------------------

void sim_data::file_to_string(std::string s_file, std::vector<std::string>& linesVect)
{
  // This function opens the file named s_file and writes it into the given
  // vector of strings linesVect, one element for each significant line.

  // First of all empty the vector
  linesVect.clear();

  // Open file
  std::cout << "Loading file '" << s_file << "'" << std::endl;
  const char * filename = s_file.c_str();

  std::ifstream filein;
  filein.open(filename);
  if (!filein) {
      std::cout << "ERROR: couldn't open file '" << filename << "'." << std::endl;
      exit(1);
  }

  std::string line; // auxiliary variable

  // read lines
  while(getline(filein, line)){

      // Parse the line
      line = parseline(line);

      // If the line is not empty, save it in a vector of strings
      if(line.length() > 0) {
         linesVect.push_back(line);
      }

  }

  return;
}

// ---------------------------------------------

void sim_data::initialize()
{
  // This function initializes the data class, by reading the
  // input file and the species file.
  // Values are written into local variables.

  // working variables..
  std::vector<std::string> linesVect;
  std::string              lineNow;
  std::stringstream        lineStream;

  // ############   READ INPUT FILE   ###################

  file_to_string(s_file_input, linesVect);

  // Check for known syntax into the vector of saved lines
  for(size_t ii = 0; ii < linesVect.size(); ++ii) {

    lineNow = linesVect.at(ii);

    // ---  Solution Type
    if(lineNow.compare("Solution Type:")==0) {
        // It's just a string, no need for a stringstream object
        this->sol_type = linesVect.at(ii+1);
    }

    // ---  Fnum
    if(lineNow.compare("Fnum:")==0) {
        lineStream.str("");                 // empty buffer and ..
        lineStream.clear();                 // .. clear the string

        lineStream.str(linesVect.at(ii+1)); // assign the string to ss object
        lineStream >> this->Fnum;           // transform string into a double
    }

    // ---  Timestep
    if(lineNow.compare("Timestep:")==0) {
        lineStream.str("");                 // empty buffer and ..
        lineStream.clear();                 // .. clear the string

        lineStream.str(linesVect.at(ii+1)); // assign the string to ss object
        lineStream >> this->dt;             // transform string into a double
    }

    // ---  Species File
    if(lineNow.compare("Species File:")==0) {
        // It's just a string, no need for a stringstream object
        this->species_file = linesVect.at(ii+1);
    }

    // ---  Collisions File 
    if(lineNow.compare("Collisions File:")==0) {
        // It's just a string, no need for a stringstream object
        this->collisions_file = linesVect.at(ii+1);
    }

    // ---  PNG exporting
    // An image is exported at each timestep
    if(lineNow.compare("PNG exporting:")==0) {
      lineStream.str("");                 // empty buffer and ..
      lineStream.clear();                 // .. clear the string

      lineStream.str(linesVect.at(ii+1)); // assign the string to ss object
      lineStream >> this->png_flag;       // transform string into a double
    }

  }

  // Variables to save read strings
  std::cout << "\nInput file was read: " << std::endl;
  std::cout << "    Solution type:   "   << this->sol_type        << std::endl;
  std::cout << "    Timestep:        "   << this->dt              << std::endl;
  std::cout << "    Fnum:            "   << this->Fnum            << std::endl;
  std::cout << "    Species file:    "   << this->species_file    << std::endl;
  std::cout << "    Collisions file: "   << this->collisions_file << std::endl;

  std::cout << std::endl;

  // ##############   READ SPECIES FILE   ###############

  std::string nameNow;       // tmp
  double massNow, chargeNow; // tmp

  file_to_string(this->species_file, linesVect);

  // Number of species is the number of non-null lines in the file:
  this->n_species = linesVect.size();

  // For each species, unpack the read line
  for(size_t id_s = 0; id_s < this->n_species; ++id_s)
  {
    lineStream.str("");                 // empty buffer and ..
    lineStream.clear();                 // .. clear the string
  
    lineStream.str(linesVect.at(id_s)); // assign the string to ss object
   
    lineStream >> nameNow >> massNow >> chargeNow;

    this->species_name.push_back(nameNow);
    this->species_mass.push_back(massNow);
    this->species_charge.push_back(chargeNow);
  }

  return;
}

