% Aidan Chin
% 12/10/23
% ECE 202: Project 1 phase 5

%---initialize---

format shortG
clear
clc


%---setup---

A = 7; %amplitude of sinusoid
w = 10; %angular frequency of sinusoid
num_terms = input("Enter number of non-zero terms of the sinusoid: ");
%number of non-zero terms
tmin = input("Enter minimum time in ms: "); %min time in ms
tmax = input("Enter maximum time in ms: "); %max time in ms
N = input("Enter number of intervals: "); %number of points for plotting

t_ms = linspace(tmin,tmax,N); % make time array t in seconds from 0s to 0.5s
t = t_ms/1000; % convert time t to ms from 0ms to 500ms

n = [0:2:(2*num_terms)-2]; % n values of non-zero coefficients
a_n = (-1).^(n/2).*(20.^n)*7./factorial(n); % a_n values of non-zero coefficients

%make a table
T = table(n',a_n','VariableNames', {'n values', ...
    'a_n values (Non-zero coefficients)'})

% ---- old calculations ----

f1 = a_n(1)*t.^n(1); % First term
f2 = f1 + a_n(2)*t.^n(2); % 1-2 term
f3 = f2 + a_n(3)*t.^n(3); % 1-3 terms
f4 = f3 + a_n(4)*t.^n(4); % 1-4 terms
f5 = f4 + a_n(5)*t.^n(5); % 1-5 terms
f6 = f5 + a_n(6)*t.^n(6); % 1-6 terms

% ---- plotting with new calc----

f = zeros([1 N]);

hold on %keeps from making new plots

for i = 1:num_terms
    f = f + a_n(i)*t.^n(i);
    if  i < 6
        p(i)=plot(t_ms,f,'LineWidth', 2);
    else
        p(i)=plot(t_ms,f,'LineWidth', 4);
        plot([tmin,tmax], [0,0], 'k', 'LineWidth', 1)
    end
end

givenFunction = A*cos(w*t); %the given function 7cos(20t)

avgDev = averageDeviation(givenFunction,f,N) % Uses function to 
% calculate average devation between given function and final function 


hold off
grid on %turn on gridlines
ax = gca; %initialize gca
ax.GridAlpha = 0.4; %change grid
ax.FontSize = 16; %change chart font size

title(sprintf("ECE 202 Project 1 Phase 5: Power series expansion \n of " + ...
    "f(t)=%gcos(%gt) up to first %g non-zero " + ...
    "terms \n with a deviation of %g",A,w,num_terms,avgDev), ...
    Interpreter='latex', FontSize=21)
%make title
xlabel("Time (t) in miliseconds","FontSize",18)
%add title for x
ylabel(sprintf("First six non-zero terms of " + ...
    "f(t)=%gcos(%gt)",A,w),Interpreter='latex',FontSize=18)
%add title for y
ylim([-1*(A+3) A+3])
%change bounds
terms = 1:num_terms;
legend(p,"terms: "+ terms + ", " + ...
    "n = " + n,Location="southoutside",FontSize=18,NumColumns=3)
%create legend automatically
if num_terms == 6
    checkf = sum(f-f6) %checks difference between old and new calculations
%should be 0
end

function ave = averageDeviation(x,y,z)
    ave = sum(abs(x-y))/z;
end
