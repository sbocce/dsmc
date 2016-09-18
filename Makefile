CMP = g++  -c 
LNK = g++
OPT = 

OBJS = mesh.o


# Main object

main.exe:  main.o  $(OBJS)
	$(LNK) $(OPT)  main.o  $(OBJS)  \
              -o main.exe

# Objects generation

main.o:                 main.cpp  $(OBJS)
	$(CMP) $(OPT)   main.cpp 

mesh.o:                 mesh.cpp
	$(CMP) $(OPT)   mesh.cpp 




clean: 
	@echo cleaning objects, modules and executables 
	rm  *.o  *.mod  *.exe
  
