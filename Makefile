# ----------------------------------
# This is the global makefile!
# Run this and you should be done.
# ----------------------------------

# Note for those like me that are complete noobs with Makefiles:
# each line of the Makefile is run on a separate shell. For this
# reason, there's no need to do a cd back into the main directory!

all:
	@echo "Preparing directory tree (making sure important directories exist!)"
	mkdir -p bin
	cd lodepng; make
	cd src;     make

clean:
	cd lodepng; make clean
	cd src;     make clean
	rm -rf bin
#	cd bin;     rm -f *.exe
