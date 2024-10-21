% Adi Nelson
% 11/10/23
% ECE 202: Project 1 phase 3

format shortG
clear
clc

% ---- Setup ----

A = 7; % Amplitude of the sinusoid

w = 20; % Angular frequency of the sinusoid

num_terms = 6; % Number of non-zero terms

tmin = 0; % Minimum time in ms

tmax = 500; % Max time in ms

intervals = 1000; % Number of points for plotting

t_ms = linspace(tmin,tmax,intervals); % Time t in seconds from 0ms to 500ms

t = t_ms/1000; % Time t in ms from 0s to 0.5s

n = [0:2:(2*6)-2]; % n values of non-zero coefficients

a_n = (-1).^(n/2).*(w.^n)*A./factorial(n); % a_n values of non-zero coefficients

T = table(n',a_n','VariableNames', {'n values', ...
    'a_n values (Non-zero coefficients)'})

% ---- Calculations ----

f1 = a_n(1)*t.^n(1); % First term
f2 = f1 + a_n(2)*t.^n(2); % First and second term
f3 = f2 + a_n(3)*t.^n(3); % First through third terms
f4 = f3 + a_n(4)*t.^n(4); % First through fourth terms
f5 = f4 + a_n(5)*t.^n(5); % First through fifth terms
f6 = f5 + a_n(6)*t.^n(6); % First through sixth terms

% ---- Plotting ----

hold on
p1 = plot(t_ms,f1,t_ms,f2,t_ms,f3,t_ms,f4,t_ms,f5,'LineWidth', 2);
p2 = plot(t_ms,f6,'LineWidth', 4);
plot([0,500], [0,0], 'k', 'LineWidth', 1)
grid on
ax = gca; 
ax.GridAlpha = 0.4;
ax.FontSize = 16;

title(sprintf("ECE 202 Project 1 Phase 3: Power series expansion \n of " + ...
    "f(t)=%gcos(%gt) up to first %g non-zero " + ...
    "terms",A,w,num_terms),Interpreter='latex',FontSize=21)
xlabel(sprintf("Time (t) in miliseconds"),Fontsize=18)
ylabel(sprintf("First six non-zero terms of " + ...
    "f(t)=%gcos(%gt)",A,w),Interpreter='latex',FontSize=18)
ylim([-1*(A+3) A+3])

legend_terms = [1:6];

legend([p1; p2],"terms: "+ legend_terms + ", " + ...
    "n = " + n,Location="southoutside",FontSize=18,NumColumns=3)

% Results are the same as Phase 2