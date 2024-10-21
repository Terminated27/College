%aidan chin
%ece202 lecture 2 intro to matlab
%09/08/2023
%find shortest stopping distance for a car on a flat road

% ---- given information ----

m = input("input mass of the car: "); %mass of car in kg
v0 = v0kph*1000/3600; vf = 0; %initial and final velocities of the car, m/s
v0kph = 100 % initial velocity of the car Km/h
%uk = 0.1; us = 0.4; %kinetic and static coefficients of friction, N/N
g = 10; % gravitational constant N/kg

% ---- Calculations ----

Fmax = -us*m*10 %largest net force, in N, answer to (a)

amax = Fmax/m %largest acceleration in m/s^2, answer to (b)
%negative acceleration, opposite direction to motion
tmin = (vf-v0)/amax; %stipping time, seconds
dmin = v0*tmin+1/2*amax*tmin^2 %stopping distance in m, asnwer to (c)

mus
% answer check
dEk = .5*m*v0*vf^2 %kinetic energy differential

dEth = abs(Fmax)*dmin; %thermal energy differential

check_energy = dEk+dEth %check energy conservation