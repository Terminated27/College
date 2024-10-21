%{
Aidan Chin M4 part D 9/27/23
ECE 202 MATLAB Exercise M4
The goal of this code is to graph Three dampings for parallel RLC
%}

% *** Prepare workspace *** 
clear % clear variables to remove chance of error
clf % clear figures to make the graph window clear

% *** Givens ***
tmsmin = 0; % minimum time in seconds
tmsmax = .05; % maximum time in seconds
N = 400; % number of steps to be made between min and max
tms = linspace(tmsmin,tmsmax,1+N);%create array of numbers between tmsmin 
                                                             % and tmsmax
% *** Calculations ***
v1 = 10*exp(-500.*tms)-5*exp(-300.*tms);
v2 = 10*exp(-400.*tms)-5000.*tms.*exp(-400.*tms);
v3 = 10*exp(-150.*tms).*cos(450.*tms)+4.*exp(-150.*tms).*sin(450.*tms);
%v1, v2, v3 are arrays filled with the respective formula to each point in array 
% tms, these are the chosen Damping for Parallel RLC formulas
tmsA = tms.*1000; % convert the seconds in tms to miliseconds in tmsA to make
%easier to read axis values

% *** Graphing ***
plot(nexttile,tmsA, v1,'red', tmsA, v2,'green', tmsA, v3, 'blue','LineWidth',3)
 % initialize plot of array and applied formula values
title('ECE 202 Exercise M4 Part (d) | Dampings for parallel RLC','FontSize',21)
legend('overdamped','critically damped','underdamped')
ylabel('Voltage (v)','FontSize',21)% change y axis label and font size
xlabel('Time (ms)','FontSize',21) % change x axis label and font size
set(gca, 'FontSize', 18) % change the axis values font size
grid on % enable the grid on the graph