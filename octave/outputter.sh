#!/bin/bash

# Nothing serious. Just creates some files..

cat output_all0 | grep "CELL 0" > outp0_cell_0.dat
cat output_all0 | grep "CELL 1" > outp0_cell_1.dat
cat output_all0 | grep "CELL 2" > outp0_cell_2.dat
cat output_all0 | grep "CELL 3" > outp0_cell_3.dat

cat output_all1 | grep "CELL 0" > outp1_cell_0.dat
cat output_all1 | grep "CELL 1" > outp1_cell_1.dat
cat output_all1 | grep "CELL 2" > outp1_cell_2.dat
cat output_all1 | grep "CELL 3" > outp1_cell_3.dat


cut -d " " -f 4- outp0_cell_0.dat > tmp && mv tmp outp0_cell_0.dat
cut -d " " -f 4- outp0_cell_1.dat > tmp && mv tmp outp0_cell_1.dat
cut -d " " -f 4- outp0_cell_2.dat > tmp && mv tmp outp0_cell_2.dat
cut -d " " -f 4- outp0_cell_3.dat > tmp && mv tmp outp0_cell_3.dat

cut -d " " -f 4- outp1_cell_0.dat > tmp && mv tmp outp1_cell_0.dat
cut -d " " -f 4- outp1_cell_1.dat > tmp && mv tmp outp1_cell_1.dat
cut -d " " -f 4- outp1_cell_2.dat > tmp && mv tmp outp1_cell_2.dat
cut -d " " -f 4- outp1_cell_3.dat > tmp && mv tmp outp1_cell_3.dat


