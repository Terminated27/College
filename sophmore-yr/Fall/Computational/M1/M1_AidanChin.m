% *** Aidan Chin ***
% *** 9/15/2023 ***
% ECE 202 MATLAB exercise M1
% Citation: http://hyperphysics.phy-astr.gsu.edu/hbase/elacol2.html

% *** Calculates the final velocity of 2 cars traveling along the same ***
% *** straight line, coliding elastically ***

clear   % clears registers, to catch mistakes


% ----- givens -----

% Left cart is #1; right cart is #2

m1 = 250; % mass, in g
m2 = 150;   % mass, in g
v1i = 30;   % initial velocity, in cm/s
v2i = 40;   % initial velocity, in cm/s

% *** short, meaningful variable names ***


% ----- calculations -----

M = m1 + m2; % define the total mass M, to make expressions more efficient ***

v1f = ((m1-m2)/M)*v1i + ((2*m2)/M)*v2i   % final velocity of cart 1, in cm/s
v2f = ((2*m1)/M)*v1i + ((m2-m1)/M)*v2i   % final velocity of cart 2, in cm/s

% *** no unnecessary parentheses ***
% *** no spaces around * and / ***
% *** add spaces around + signs, to emphasize the hierarchy of operations ***
% *** no spaces around - signs in (m1-m2) and (m2-m1), no hierarchy ***
% *** pull out factor of 1/M to make the expressions compact, efficient ***


% ----- check two conservation laws -----

% *** first one ***

checkmomentum = (m1*v1i + m2*v2i) - (m1*v1f + m2*v2f)   % *** Should be zero, checks concervation of momentum
           % *** add the name or symbol to "check", e.g., checkP or checkMomentum
           

% *** second one ***

checkkinetic = (.5*m1*v1i^2) + (.5*m2*v2i^2) - ((.5*m1*v1f^2) + (.5*m2*v2f^2))   % *** should equal zero, checks concervation of kinetic energy
           % *** add the name or symbol to "check" using the same convention