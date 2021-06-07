clear; clc; close all;
vol = 2.258e+005;
rho = 1025;
L = 295;
modalNum = 10;
%
figure(1)
hold on;
krs = load('case_FREQ/Krs.out');
num = 3;
plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'-b');
num = 5;
plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'-r');
krs = load('output_TDGF/Krs.out');
num = 3;
%plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'-b');
num = 5;
%plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'-r');
krs = load('output_IORM/Krs.out');
num = 3;
plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'--k');
num = 5;
plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'--g');
krs = load('case_TDGF/Krs.out');
num = 3;
%plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'*b');
num = 5;
%plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'*r');
krs = load('case_IORM/Krs.out');
num = 3;
plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'ok');
num = 5;
plot(krs(:,1)*sqrt(9.81/L*2),  krs(:,1 + (num-1)*modalNum + num)/(vol*rho)*L/2/9.81,'og');

legend('K33-FREQ', 'K55-FREQ', 'Old-K33-TDGF', 'Old-K55-TDGF', 'Old-K33-IORM', ...
    'Old-K55-IORM', 'New-K33-TDGF', 'New-K55-TDGF', 'New-K33-IORM', 'New-K55-IORM');