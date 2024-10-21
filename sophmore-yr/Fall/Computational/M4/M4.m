clear
clf
% Givens
t = linspace(0,5,400);
x = linspace(-6,6,400);
x2 = 8;
tms = linspace(0,.05,400);
f = 1+t./2-(t.^2)/3;
g = 5 * sin(2 * (x-3));
P = 1/(2*sqrt(pi)) * exp(-(x-4).^2/4);
v1 = 10*exp(-500.*tms)-5*exp(-300.*tms);
v2 = 10*exp(-400.*tms)-5000.*tms.*exp(-400.*tms);
v3 = 10*exp(-150.*tms).*cos(450.*tms)+4.*exp(-150.*tms).*sin(450.*tms);

%initialize graph
tiledlayout(2,2)
% graphing

% graph f, the truncated power series
plot(nexttile,t,f,'LineWidth',3);
title('ECE	202, Exercise M4, part (a) | Truncated Power Series','FontSize',21);
xlabel('Time t (s)','FontSize',21)
ylabel('f(t)','FontSize',21)
set(gca, 'FontSize', 18);

plot(nexttile,x,g,'red','LineWidth',3);
ylim([-6,6]);
title('ECE	202, Exercise M4, part (b) | Shifted Sinusoid','FontSize',21);
xlabel('Distance x (m)','FontSize',21);
ylabel('g(x)','FontSize',21);
set(gca, 'FontSize', 18);

plot(nexttile,x2,P,'LineWidth',3);
title('ECE 202 Exercise M4 part (c) | Normalized Gaussian', 'FontSize',24);
ylabel('P(x) in inverse meters (m^{-1})','FontSize',21);
xlabel('Distance x (m)','FontSize',21);
set(gca, 'FontSize', 18);

tmsA = tms.*100;
plot(nexttile,tmsA, v1,'red', tmsA, v2,'green', tmsA, v3, 'blue','LineWidth',3);
title('ECE 202 Exercise M4 Part (d) | Dampings for parallel RLC','FontSize',21)
legend('overdamped','critically damped','underdamped');
ylabel('Voltage (v)','FontSize',21);
xlabel('Time (ms)','FontSize',21)
set(gca, 'FontSize', 18);

% check if c is accurate

CheckP = trapz(x,P) %should be about 1

