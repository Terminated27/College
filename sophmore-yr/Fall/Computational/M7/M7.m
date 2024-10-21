%{
Aidan Chin
ECE 202
Exercise M7
11/15/2023
the purpose of this script is to compute and plot
i(t) v(t) p(t) and wf in a RL circuit 
%}
%-----Inititalize-----
clear %clear var to set up script

%-----Given-----
v0 = 5; %initial voltage in Volts
L = 10; %inductance of inductor in MilliHenries
R = 2; %resistance of resistor in Ohms
tau = L/R; %time constant
n = 400; %number of steps to make in time array
t0 = 0; %initial time
tf = 10*tau;
t = linspace(t0,tf, n+1); %array of time, in milliseconds
et = exp(-t./tau); %e^{t/tau}, used more than once so declared to save typing
VovrR = v0/R; %calculate this for the formula printout & subsequently the formula too
itf = "\(i(t) = "+num2str(VovrR)+" \cdot e^{-\frac{t}{"+num2str(tau)+"}} \)";
vtf = "\(v(t) = "+num2str(v0)+"\cdot e^{-\frac{t}{"+num2str(tau)+"}} \)";
ptf = "\(v(t) \cdot i(t)\)";

%-----Calculations-----
it = VovrR .* (1-et); %the current Amps as a function of time milliseconds
vt = v0.*et; %the current voltage as a function of time in milliseconds
pt = it.*vt; %the current power consumption of the circuit as a function of 
             % time in milliseconds
ifin = VovrR; %calculate final energy stored 
w = .5*L * ifin^2; %total energy stored in joules in the inductor as a function 
                   %of time in milliseconds

%-----Checks-----
check_ab = trapz(pt) - w
perc_err = 100*(sum(pt)-w)/w
%-----Plotting-----
tiledlayout(3,1)
sgtitle({"RL ciruit in series: Current, voltage, and power absorbed", ...
    "for a charvhing inductor (V_0="+num2str(v0)+"V, R="+num2str(R)+"\Omega," + ...
    " L="+num2str(L)+"mH)"},'fontsize',25,'fontname','Times New Roman');
itp = nexttile;
plot(itp,t, it,'LineWidth',2,'Color','red');
ylim(itp,[0,3])
ylabel('Current in Amps')
text(itp, 30, 1, itf, 'Interpreter','latex','FontSize',15)

vtp = nexttile;
plot(vtp, t, vt,'LineWidth',2,'Color','blue');
ylim(vtp,[0,6])
text(vtp, 30, 2, vtf, 'Interpreter','latex','FontSize',15)
ylabel('Voltage in Volts')

ptp = nexttile;
plot(ptp, t, pt,'LineWidth',2, 'Color','green');
text(ptp, 30, 1, ptf, 'Interpreter','latex','FontSize',15)
xlabel(ptp,'Time (t) in ms')
ylabel('Power Consumption in Joules')


