%{
Aidan Chin M5 9/29/23
ECE 202 MATLAB Exercise M5
The goal of this code is to demonstrate that the product of 2 sinusoids can
be written as the sum of 2 sinusoids

Essentially using Product to Sum Identity of Sinusoids
 ---- cos(a)*cos(b) = 1/2(cos(a+b) + cos(a-b)) ----
Citation for formulas: http://hyperphysics.phy-astr.gsu.edu/hbase/trid.html
%}

% *** Prepare workspace *** 
clear % clear variables to remove chance of error
clf % clear figures to make the graph window clear


% *** Givens ***
tmax = -.1; % minimum time, in seconds (s)
tmin = .1; % maximum time, in seconds (s)
N = 400; % number of steps in the graph
t = linspace(tmax,tmin,N+1); % create array of N+1 numbers between tmax and tmin


% *** Calculation ***
a = 40.*t - 1.2; % inside value for first cos
b = 60.*t + 1.8; % inside value for second cos
f = 10 * cos(a) .* cos(b); % given cosine multiplication formula
f1 = 5 * cos(a+b); % first term in equivalent addition formula
f2 = 5 * cos(a-b); % second term in equivalent addition formula
tms = t.*1000; % convert seconds to miliseconds (more readable)


% *** Check ***
d = abs(f1+f2) - abs(f); % check to make sure the 2 formulas are equivalent
check = sum(d) % print single number check, should be close to 0

% the reason we use abs intead of soley sum is because you want to find the
% distance of the 2 graphs from eachother, and distance is always positive

% *** Graphing ***
plot(tms,f,tms,f1,tms,f2,tms,d,'linewidth',2) 
%plot all 3 formulas and check on one graph with linewidth 2
title({'Showing That 10*cos(40t-1.2)*cos(60t+1.8)' ...
    'Could Be Written As' ...
    '5*cos(40t-1.2 - 60t+1.8) + 5*cos(40t-1.2 - 60t + 1.8)'})
% make a 3 line title
legend('f = [10 * cos(40t-1.2) * cos(60t+1.8)]', ...
    'f1 = [5 * cos(40t-1.2 + 60t+1.8)]','f2 = [5 * cos(40t-1.2 - 60t+1.8)]', ...
    'Check = [|f1+f2| - |f|], should be 0')
% make a legend for each graphed line
ylabel('Voltage (V)')% change y axis label
xlabel('Time (ms)') % change x axis label
ylim([-11,11]) % change y limits in graph to prevent overlap with the legend
grid on % enable grid on graph
