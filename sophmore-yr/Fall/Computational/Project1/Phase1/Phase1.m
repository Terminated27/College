% Aidan Chin
% 12/10/23
% ECE 202: Project 1 phase 2

%---initialize---

format shortG
clear
clc

%---setup---

t = linspace(0,0.5,1000); % make time array t in seconds from 0s to 0.5s

n = [0:2:10] % n values of non-zero coefficients
a_n = (-1).^(n/2).*(20.^n)*7./factorial(n) % a_n values of non-zero coefficients

% ---- calculations ----

f1 = a_n(1)*t.^n(1); % First term
f2 = f1 + a_n(2)*t.^n(2); % 1-2 term
f3 = f2 + a_n(3)*t.^n(3); % 1-3 terms
f4 = f3 + a_n(4)*t.^n(4); % 1-4 terms
f5 = f4 + a_n(5)*t.^n(5); % 1-5 terms
f6 = f5 + a_n(6)*t.^n(6); % 1-6 terms

% ---- plotting ----


%plot values
p1 = plot(t,f1,t,f2,t,f3,t,f4,t,f5,t,f6); 

grid on %turn on gridlines

title({"ECE 202 Project 1 Phase 1: Power series expansion", ...
    "of f(t)=7cos(20t) up to first 6 non-zero terms"})
%make title
xlabel("Time (t) in miliseconds")
%add title for x
ylabel("First six non-zero terms of f(t)=7cos(20t)")
%add title for y
ylim([-10 10])
%change bounds
