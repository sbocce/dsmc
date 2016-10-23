# Hello! :)

CMP = g++  -c 
LNK = g++

# I need the headers of lodepng, that are in main_dir/lodepng
OPT = -I../lodepng

OBJS =  solver.o  exporter.o  mesh.o  cell.o  particle.o  stat_tools.o


# Main object

main.exe:  main.o  $(OBJS)
	$(LNK) $(OPT)  main.o  $(OBJS) ../lodepng/lodepng.o \
              -o ../bin/main.exe

# Objects generation

main.o:                 main.cpp  $(OBJS)
	$(CMP) $(OPT)   main.cpp 

solver.o:               solver.cpp  particle.o
	$(CMP) $(OPT)   solver.cpp

exporter.o:             exporter.cpp  mesh.o
	$(CMP) $(OPT)   exporter.cpp

mesh.o:                 mesh.cpp  cell.o  particle.o  stat_tools.o
	$(CMP) $(OPT)   mesh.cpp 

cell.o:                 cell.cpp
	$(CMP) $(OPT)   cell.cpp

particle.o:             particle.cpp
	$(CMP) $(OPT)   particle.cpp

stat_tools:             stat_tools.cpp
	$(CMP) $(OPT)   stat_tools.cpp

clean: 
	@echo cleaning objects, modules and executables 
	rm -f  *.o  *.mod  *.exe
  
