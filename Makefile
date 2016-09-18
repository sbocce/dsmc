CMP = g++  -c 
LNK = g++
OPT = 

OBJS =  mesh.o  cell.o  stat_tools.o


# Main object

main.exe:  main.o  $(OBJS)
	$(LNK) $(OPT)  main.o  $(OBJS)  \
              -o main.exe

# Objects generation

main.o:                 main.cpp  $(OBJS)
	$(CMP) $(OPT)   main.cpp 

mesh.o:                 mesh.cpp  cell.o  stat_tools.o
	$(CMP) $(OPT)   mesh.cpp 

cell.o:                 cell.cpp
	$(CMP) $(OPT)   cell.cpp

stat_tools:             stat_tools.cpp
	$(CMP) $(OPT)   stat_tools.cpp

clean: 
	@echo cleaning objects, modules and executables 
	rm  *.o  *.mod  *.exe
  
