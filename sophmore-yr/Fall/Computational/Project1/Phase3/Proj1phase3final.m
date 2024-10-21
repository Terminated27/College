% Aidan Chin
% 12/10/23
% ECE 202: Project 1 phase 3

%---initialize---

format shortG
clear
clc

%---setup---

A = 7; %amplitude of sinusoid
w = 10; %angular frequency of sinusoid
num_terms = 6; %number of non-zero terms
tmin = 0; %min time in ms
tmax = 500; %max time in ms
N = 1000; %number of points for plotting

t_ms = linspace(tmin,tmax,N); % make time array t in seconds from 0s to 0.5s
t = t_ms/1000; % convert time t to ms from 0ms to 500ms

n = [0:2:10]; % n values of non-zero coefficients
a_n = (-1).^(n/2).*(20.^n)*7./factorial(n); % a_n values of non-zero coefficients

%make a table
T = table(n',a_n','VariableNames', {'n values', ...
    'a_n values (Non-zero coefficients)'})

% ---- calculations ----

f1 = a_n(1)*t.^n(1); % First term
f2 = f1 + a_n(2)*t.^n(2); % 1-2 term
f3 = f2 + a_n(3)*t.^n(3); % 1-3 terms
f4 = f3 + a_n(4)*t.^n(4); % 1-4 terms
f5 = f4 + a_n(5)*t.^n(5); % 1-5 terms
f6 = f5 + a_n(6)*t.^n(6); % 1-6 terms

% ---- plotting ----


hold on %keeps from making new plots
p1 = plot(t_ms,f1,t_ms,f2,t_ms,f3,t_ms,f4,t_ms,f5,'LineWidth', 2); 
%plot first 5 coefficients
p2 = plot(t_ms,f6,'LineWidth', 4); %plot 6th coefficient as thicker
plot([0,500], [0,0], 'k', 'LineWidth', 1) %plot horizontal line
grid on %turn on gridlines
ax = gca; %initialize gca
ax.GridAlpha = 0.4; %change grid
ax.FontSize = 16; %change chart font size

title(sprintf("ECE 202 Project 1 Phase 3: Power series expansion \n of " + ...
    "f(t)=%gcos(%gt) up to first %g non-zero " + ...
    "terms",A,w,num_terms),Interpreter='latex',FontSize=21)
%make title
xlabel("Time (t) in miliseconds","FontSize",18)
%add title for x
ylabel(sprintf("First six non-zero terms of " + ...
    "f(t)=%gcos(%gt)",A,w),Interpreter='latex',FontSize=18)
%add title for y
ylim([-1*(A+3) A+3])
%change bounds
terms = 1:6;
legend([p1; p2],"terms: "+ terms + ", n = " + n,Location="southoutside", ...
    FontSize=18,NumColumns=3)
%create legend automatically
%results are the same as phase 2
