%{
Aidan Chin Midterm 1 part 3 D 10/4/23
ECE 202 MATLAB Midterm 1
the goal of this script is to show that sin(3wt) is equal to 3sin(wt)
-4sin^3(wt)
%}

% *** Prepare workspace *** 
clear % clear variables to remove chance of error
clf % clear figures to make the graph window clear

% *** Givens ***
w = input('Input value of w: '); % angular momentum in radians/second
tmin = -pi/w; % minimum t value
tmax = -1 * tmin; % maximum t value
N = 1000; % number of steps to be made between min and max
t = linspace(tmin,tmax,1+N);%create array of numbers between tmin 
                                                             % and tmax

% *** Calculation ***
a = w.*t; % define a so avoid writing many times later
f1 = sin(3.*a); % given sine formula
f2 = 3*sin(a) - 4*sin(a).^3; % given sine subtraction formula

% *** Check ***
d = abs(f2) - abs(f1); % check to make sure the 2 formulas are equivalent
check = sum(d) % print single number check, should be close to 0

% the reason we use abs intead of soley sum is because you want to find the
% distance of the 2 graphs from eachother, and distance is always positive

% *** Graphing ***
if tmin <= -.1 %check if time values are larger than .1 to see if should be in ms
    plot(t,f1,t,f2,':','LineWidth',3) %plot both formulas on graph with f1 being 
    %solid line, f2 being dotted and linewidth of 3
    xlabel('Time (s)') % change x axis label
else
    tms = t.*1000;
    plot(tms,f1,tms,f2,':','LineWidth',3) %plot both formulas on graph with f1 being 
    %solid line, f2 being dotted and linewidth of 3
    xlabel('Time (ms)') % change x axis label
end

title('ECE 202 Midterm 1 Part 3 D', ...
    'Proving that sin(3wt) \equiv 3sin(wt) - 4sin^3(wt)')
%make title and description of figure
legend('f1 = sin(3wt)','f2 = 3sin(wt) - 4sin^3(wt)') % make legend for figure
ylabel('Angular Momentum (radians/second)')% change y axis label 
ylim([-1.5,1.5]) % modify the y axis limits so no overlap on legend
grid on % enable the grid on the graph
