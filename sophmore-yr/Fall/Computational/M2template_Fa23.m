% *** Aidan Chin ***
% *** 9/15/23 ***
% ECE 202 MATLAB exercise M2

% *** citation: http://hyperphysics.phy-astr.gsu.edu/hbase/elacol2.html

% *** description: the goal of this code is to determine the mass of object
% 2 and final velocity of object 1 in elastic collision


clear   % clears the registers, which helps catch typos


% ----- givens -----

% Left cart is #1; right cart is #2

m1 = input("Input value for mass of car (g): " ); % mass for car 1 in g
v1i = input("Input value for intial velocity of car (cm/s): "); % initial velocity in cm/s
v2i = -v1i; % initial veloctiy in cm/s
v2f = 0; % final velocity in cm/s


% ----- calculation -----


m2 =  m1*(2*v1i - v2i - v2f) / (v2f - v2i) % mass for car 2 in g

        % *** expression for m2 must depend on all 4 givens
        
M = m1 + m2; %total mass of the 2 cars in g

v1f = ((m1-m2)/M)*v1i + ((2*m2)/M)*v2i   % final velocity of cart 1, in cm/s

        % *** expressions for v1f (below) and v2f are from M1 ***




% ----- check conservation of momentum and energy -----

checkP = (m1*v1i + m2*v2i) - (m1*v1f + m2*v2f)   % *** should be zero, checks concervation of momentum


% initial and final kinetic energies, in *** J/100000 ***

KEi = (.5*m1*v1i^2) + (.5*m2*v2i^2);
KEf = (.5*m1*v1f^2) + (.5*m2*v2f^2);

checkKE = KEi - KEf   % *** should be zero, kinetic energy must be conserved


% ----- check that design is successful -----

check_v2f = v2f - (((2*m1)/M)*v1i + ((m2-m1)/M)*v2i)   % should be equal to v2f, difference should = 0

% *** Alternatively, compute v2f_new = ... using expression from M1

% *** this code is successful because the checks all came out as expected,
% and the values are logical.