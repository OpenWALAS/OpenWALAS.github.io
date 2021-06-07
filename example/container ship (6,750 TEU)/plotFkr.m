%plot the curve of impluse response function of F-K force
clear; clc; close all;
vol = 2.258e+005;
rho = 1025;
L = 295;
angle = 1;
modal = 10;

figure(1)
hold on;
krs = load('case_FREQ/Fkr.out');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'-b');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'-r');
krs = load('output_TDGF/Fkr.out');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'.b');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'.r');
krs = load('output_IORM/Fkr.out');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'--k');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'--g');
krs = load('case_TDGF/Fkr.out');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'*b');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'*r');
krs = load('case_IORM/Fkr.out');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +3)/(rho*9.81*pi*L)/sqrt(9.81*L),'ok');
plot(krs(:,1)*sqrt(9.81/L), krs(:,1 + (angle-1)*modal +5)/(rho*9.81*pi*L)/sqrt(9.81*L),'og');
%
grid on;
legend( 'Fkr3-FREQ', 'Fkr5-FREQ','Old-Fkr3-TDGF', 'Old-Fkr5-TDGF', 'Old-Fkr3-IORM', ...
    'Old-Fkr5-IORM', 'New-Fkr3-TDGF', 'New-Fkr5-TDGF', 'New-Fkr3-IORM', 'New-Fkr5-IORM');

%yy = load('k37.txt');
%plot(yy(:,1)/sqrt(2), yy(:,2),'.r');
%legend('Present', 'King');