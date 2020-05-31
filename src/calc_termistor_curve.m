clc; clear all; close all;
% This is to approximate how the resistance in the termistor changes using
% an approximation

T = 0:1:32;
R = [32.960 31.3081 29.7487 28.2760 26.8848 25.5702 24.3274 23.1523 22.0407 20.9889...
     19.9934 19.0509 18.1582 17.3124 16.5109 15.7511 15.0306 14.3472 13.6987 13.0833...
     12.4990 11.9441 11.4169 10.9161 10.4400 10.0000 9.55693 9.14743 8.75777 8.38690...
     8.03380 7.69753 7.37721 ]*10^3;

R100 = 0.6744 * 10^3;
R50 = 3.588 * 10^3;
R0 = 32.96 * 10^3;

T100 = cel_to_kel(100);
T50 = cel_to_kel(50);
T0 = cel_to_kel(0);

% Calculate the 3 constants in the approximation
syms a b c
exp_b = (1/T50 - a - c*log(R50)^3)/log(R50);
exp_c = (1/T0 - a - b*log(R0))/(log(R0)^3);
exp_a = 1/T100 - b*log(R100)-c*log(R100)^3; 

exp_b = subs(exp_b, a, exp_a);
exp_b = simplify(b==exp_b);

exp_c = subs(exp_c, a, exp_a);
exp_c = subs(exp_c, b, solve(exp_b, b));
c_val = solve(exp_c, c);

b_val = solve(subs(exp_b, c, c_val), b);
a_val = subs(subs(exp_a, b, b_val), c, c_val);


% These values are taken from an example
%a_val = 0.001125308852122;
%b_val = 0.000234711863267;
%c_val = 0.000000085663516;


T_est = @(R) (a_val + b_val*log(R(:)) + c_val*log(R(:)).^3).^-1;

u_max = 3;
u_in = 3.3;
syms R1 u_min
R1 = solve(u_max == u_in*R1/(R1+R100));
u_min = solve(u_min == R1*u_in/(R1+R0));

R = @(u) R1*3.3./u(:)-R1;
T_est_u = @(u)  kel_to_cel(1./(a_val + b_val.*log(R(u)) + c_val*log(R(u)).^3));

u = u_max:-0.01:u_min;
plot(u, T_est_u(u))
legend('R(u)')

%%
function t = cel_to_kel(t)
    t = t + 273.15;
end

function t = kel_to_cel(t)
    t = t - 273.15;
end