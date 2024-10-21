%{
Aidan Chin
ECE 202
Exercise M8
11/15/2023
the purpose of this script is to find the three coefficients, c1, c2, and c3.
when doing partial fraction decomposition

%}
%initialize
clear

%givens (create system of equations in terms of all 3 variables)
A=[1  1  1; 
  -5 -4 -3; 
   6  3  2]; % 3 x 3 matrix representing (6x^2+5x+4)/((x-1)(x-2)(x-3))

b=[6; 5; 4]; % create column matrix of the constants in the equation 6x^2+5x+4

%Calculation

r = A^(-1)*b %calculate the 3 numerators

%Checks

%given
while 1 %loop infinitely
    n = input('input number of test numbers (input 0 to break): '); 
    %ask user how many test inputs to use
    if n == 0 %check if input == 0
        fprintf('Exiting Simulation.\n') %tell user what happening
        break %exit loop
    end
    xmin = -4; %min value of x
    xmax = 4; %max value of x
    x = linspace(xmin,xmax,n); %make array of values between xmin and xmax with 
    %number of steps
    
    %initialize values of denominators
    d1 = x-1; 
    d2 = x-2;
    d3 = x-3;
    
    %calculation
    n = 6.*x.^2+5*x+4; %calculate numerator values
    y1 = n./(d1.*d2.*d3); %calculate the numerical value of equation with fraction
    % decomposition
    y2 = r(1)./d1 + r(2)./d2 + r(3)./d3; %calculate numerical value of equation
    % with original formula
    check = sum(abs(y1) - abs(y2)) %compare values, should be close to 
    % zero because values are equiv
end

%the reason the check sometimes returns NaN is because the linspace set
%will contain the roots of the equation, you are unable to divide by zero
%so the check will return an error value. with linspace 5, the set will
%contain -4, -2, 0, 2, 4
%2 is in this set, and 2 is a root.