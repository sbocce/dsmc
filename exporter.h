#ifndef EXPORTER_H
#define EXPORTER_H

#include "mesh.h"

class exporter {

  public:
    exporter(mesh* p_msh);
    ~exporter(){};
    void export_mesh_VTK(const char* filename); 
    void export_partpercell_VTK(const char* filename); // TEMPORARY EXPORTING FUNCTION

  private:
    mesh*   p_mesh;
};

#endif /* EXPORTER_H */
