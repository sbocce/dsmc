#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>     /* system, exit, EXIT_FAILURE */


#include "sim_data.h"


sim_data::sim_data(std::string s_file_input) 
{ 
  this->s_file_input = s_file_input;
  this->initialize();
}

// ---------------------------------------------

void sim_data::initialize()
{
  std::cout << std::endl;

  read_input_file();


  std::cout << " ATTENTION: sim_data::initialize() should read an input file and pick the DeltaT for example!\n";
  std::cout << "            hard-coded for now!\n";


  dt   = 0.0001; // <<<-----------------  HHHAAAAAARD COOOODED!!!!!
  Fnum = 1000;   // <<<-----------------  HHHAAAAAARD COOOODED!!!!!

  sol_type = "1D";

  std::cout << "Ciao!" << std::endl;
  return;
}

// ---------------------------------------------

double sim_data::get_dt()
{
  return this->dt;
}

// ---------------------------------------------

const char* sim_data::get_sol_type()
{
  return this->sol_type;
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

void sim_data::read_input_file()
{

  std::cout << "Loading Input file '" << s_file_input << "'" << std::endl;

  // Open file
  const char * filename = s_file_input.c_str();

  std::ifstream filein;
  filein.open(filename);
  if (!filein) {
      std::cout << "ERROR: couldn't open input file." << std::endl;
      exit(1);
  }

//  // Initializing variables to value "empty"
//  s_mixture      = "empty";
//  s_state_model  = "empty";
//  s_thermo_db    = "empty";
//
//  // Auxiliary variables
//  std::string line;
//  std::vector<std::string> linesVect;
//
//  // read lines
//  while(getline(filein, line)){
//
//      // Parse the line
//      line = parseline(line);
//
//      // If the line is not empty, save it in a vector of strings
//      if(line.length() > 0) {
//         linesVect.push_back(line);
//      }
//
//  }
//
//
//  // Check for known syntax into the vector of saved lines
//  std::string lineNow;
//  for(size_t ii = 0; ii < linesVect.size(); ++ii) {
//
//    lineNow = linesVect.at(ii);
//
//    if(lineNow.compare("Problem Type:")==0) {
//        s_problem_type = linesVect.at(ii+1);
//    }
//    if(lineNow.compare("Name of the mixture:")==0) {
//        s_mixture = linesVect.at(ii+1);
//    }
//    if(lineNow.compare("State Model:")==0) {
//        s_state_model = linesVect.at(ii+1);
//    }
//    if(lineNow.compare("Thermodynamic Database:")==0) {
//        s_thermo_db = linesVect.at(ii+1);
//    }
//    if(lineNow.compare("Mesh:") == 0) {
//        s_mesh = linesVect.at(ii+1);
//    }
//    if(lineNow.compare("Free Stream Conditions:") == 0) {
//        s_free_stream_conditions = linesVect.at(ii+1);
//    }
//  }
//
//  // Variables to save read strings
//  std::cout << "\nInput file was read: "                  << std::endl;
//  std::cout << "    Problem Type: "                       << s_problem_type            << std::endl;
//  std::cout << "    Mixture: "                            << s_mixture                 << std::endl;
//  std::cout << "    State Model: "                        << s_state_model             << std::endl;
//  std::cout << "    Thermodynamic Database: "             << s_thermo_db               << std::endl;
//  std::cout << "    Mesh (TEMPORARY): "                   << s_mesh                    << std::endl;
//  std::cout << "    Free Stream Conditions (TEMPORARY): " << s_free_stream_conditions  << std::endl;
//  std::cout << std::endl;
//
  return;
}

