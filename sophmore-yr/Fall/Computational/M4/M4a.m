%{
Aidan Chin M4 part A 9/27/23
ECE 202 MATLAB Exercise M4
The goal of this code is to graph a truncated power series
%}

% *** Prepare workspace *** 
clear % clear variables to remove chance of error
clf % clear figures to make the graph window clear

% *** Givens *** 
tmin = 0; %minimum time in seconds
tmax = 5; %maximum time in seconds
N = 400; % number of steps to be made between min and max
t = linspace(tmin,tmax,1+N); %create array of numbers between tmin and tmax

% *** Calculation *** 
f = 1 + t./2 - (t.^2)/3; %array filled by applying formula to each point in 
% array t this is the chosen truncated power series formula

% *** Graphing *** 
plot(t,f,'LineWidth',3); % initialize plot of array and applied formula values
title('ECE	202, Exercise M4, part (a) | Truncated Power Series','FontSize',21);
% change title and font size of title ^
xlabel('Time t (s)','FontSize',21) % change x axis label and font size
ylabel('f(t)','FontSize',21) % change y axis label and font size
set(gca, 'FontSize', 18); % change the axis values font size
grid on % enable the grid on the graph