%plot the curve of impluse response function of F-K force
clear; clc; close all;
vol = 2.258e+005;
rho = 1025;
L = 295;
angle = 1;
modal = 10;

figure(1)
hold on;
krs = load('case_FREQ/Fdr.out');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'-b');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'-r');
krs = load('output_TDGF/Fdr.out');
%plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'.-b');
%plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'.-r');
krs = load('output_IORM/Fdr.out');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'--k');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'--g');
krs = load('case_TDGF/Fdr.out');
%plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'*b');
%plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'*r');
krs = load('case_IORM/Fdr.out');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'ok');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'og');
%
grid on;
legend( 'Fdr3-FREQ', 'Fdr5-FREQ','Old-Fdr3-TDGF', 'Old-Fdr5-TDGF', 'Old-Fdr3-IORM', ...
    'Old-Fdr5-IORM', 'New-Fdr3-TDGF', 'New-Fdr5-TDGF', 'New-Fdr3-IORM', 'New-Fdr5-IORM');