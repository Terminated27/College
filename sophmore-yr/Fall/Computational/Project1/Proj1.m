%{
Aidan Chin
ECE 202 
Nov 20 2023
Project 1 part 1b
plot a power series expansion for f(t) from t=0 to t=.5s using truncated
sums starting with the first non zero term then the first two non zero terms,
ect. up to the first 6 non-zero terms
%}
clear
format shortG


%givens
tmin = 0;
tmax = .5;
N = 400;
t = linspace(tmin, tmax, N)



