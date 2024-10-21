%{
Aidan Chin M4 part C 9/27/23
ECE 202 MATLAB Exercise M4
The goal of this code is to graph a Normalized Gaussian
%}

% *** Prepare workspace *** 
clear % clear variables to remove chance of error
clf % clear figures to make the graph window clear

% *** Givens *** 
xmin = 0; %minimum distance in meters
xmax = 8; %maxiumum distance in meters 
N = 400; % number of steps to be made between min and max
x=linspace(xmin,xmax,1+N);%create array of numbers between xmin and xmax

% *** Calculation *** 
P = 1/(2*sqrt(pi)) * exp(-(x-4).^2/4); %array filled with points from applying 
% formula to each point in array x this is the chosen Normalized Gaussian formula

% *** Graphing *** 
plot(x,P,':','LineWidth',3) % initialize plot of array and applied formula values
title('ECE 202 Exercise M4 part (c) | Normalized Gaussian', 'FontSize',24)
% change title and font size of title ^
ylabel('P(x) in inverse meters (m^{-1})','FontSize',21)% change y axis label 
                                                       % and font size
xlabel('Distance x (m)','FontSize',21) % change x axis label and font size
set(gca, 'FontSize', 18) % change the axis values font size
grid on % enable the grid on the graph

% *** Checks *** 
%the area under a gaussian curve should be close to 1
%integrating the graph should yeild close to one, checking the distance
%from one should return almost zero value
CheckP = 1 - trapz(x,P) %should be about 0