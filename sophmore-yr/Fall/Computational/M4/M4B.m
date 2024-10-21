%{
Aidan Chin M4 part B 9/27/23
ECE 202 MATLAB Exercise M4
The goal of this code is to graph a Shifted Sinusoid
%}

% *** Prepare workspace *** 
clear % clear variables to remove chance of error
clf % clear figures to make the graph window clear

% *** Givens *** 
xmin = -6; % minimum distance in meters
xmax = 6; % maximum distance in meters
N = 400;  % number of steps to be made between min and max
x = linspace(xmin,xmax,1+N); %create array of numbers between xmin and xmax

% *** Calculation *** 
g = 5 * sin(2 * (x-3)); %array filled with points applied from formula to 
% each point in array x this is the chosen Shifted Sunusoid formula 

% *** Graphing *** 
plot(x,g,'red','LineWidth',3) % initialize plot of array and applied formula values
ylim([xmin,xmax]) %set a predetermined window limits for y axis
title('ECE	202, Exercise M4, part (b) | Shifted Sinusoid','FontSize',21)
% change title and font size of title ^
xlabel('Distance x (m)','FontSize',21)% change x axis label and font size
ylabel('g(x)','FontSize',21)% change y axis label and font size
set(gca, 'FontSize', 18) % change the axis values font size
grid on % enable the grid on the graph