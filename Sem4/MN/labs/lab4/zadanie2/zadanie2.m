close all

[xvec,xdif,xsolution,ysolution,iterations] = impedance_bisection();
disp(['xsolution = ', num2str(xsolution), ' Hz']);
disp(['ysolution = ', num2str(ysolution)]);
disp(['iterations = ', num2str(iterations)]);