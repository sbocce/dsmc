close all
clear
clc

% Load files
dd0_0 = load('outp0_cell_0.dat');
dd0_1 = load('outp0_cell_1.dat');
dd0_2 = load('outp0_cell_2.dat');
dd0_3 = load('outp0_cell_3.dat');

dd1_0 = load('outp1_cell_0.dat');
dd1_1 = load('outp1_cell_1.dat');
dd1_2 = load('outp1_cell_2.dat');
dd1_3 = load('outp1_cell_3.dat'); 

% Extract stuff from here
figure
subplot(2,1,1)
hold on
plot(dd0_0(:,2), dd0_0(:,3), 'or')
plot(dd0_1(:,2), dd0_1(:,3), 'ob')
plot(dd0_2(:,2), dd0_2(:,3), 'or')
plot(dd0_3(:,2), dd0_3(:,3), 'ob')

ylabel('y axis')

xlim([-2,4])
ylim([0,1])

subplot(2,1,2)
hold on
plot(dd0_0(:,2), dd0_0(:,4), 'or')
plot(dd0_1(:,2), dd0_1(:,4), 'ob')
plot(dd0_2(:,2), dd0_2(:,4), 'or')
plot(dd0_3(:,2), dd0_3(:,4), 'ob')

ylabel('z axis')
xlim([-1.5,3.5])
ylim([-0.5,0.5])



