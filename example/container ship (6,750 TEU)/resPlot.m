clear;clc;close all;
NN = 7;
A = 1;
w = 0.45;
coeff = 2.083e10/(1025*9.81*286.6^2*40*A);
%5.463
line_color = 'k';

%%%%%%
figure(1)
xm = load('output/xm1.tim');
x = xm(:,1)*sqrt(9.81/286.6);
y = xm(:,NN+1)*coeff;
plot(x, y,line_color);
%2
hold on;
amp = 2.212e-002;
ang = 179.570;
real = amp*cos(-w*xm(:,1)+ang*pi/180);
y1 = real*coeff;
plot(xm(:,1)*sqrt(9.81/286.6), real*coeff, '.-k');
%
legend('Method in time domain','Result from frequency domain');
xlabel('t*sqrt(g/L)');
ylabel('VBM/\rho*L*B^2*g');

%heave
coeff = 1/A;
figure(2)
plot(xm(:,1)*sqrt(9.81/286.6), xm(:,3+1)*coeff,line_color);
%2
hold on;
amp = 2.769e-001;
ang = -21.771;
real = amp*cos(-w*xm(:,1)+ang*pi/180);
plot(xm(:,1)*sqrt(9.81/286.6), real*coeff, '.-k');
%
legend('Method in time domain','Result from frequency domain');
xlabel('t*sqrt(g/L)');
ylabel('Heave/A');

%pitch
T = 2*pi/w;
L = T^2/0.64;
k = 2*pi/L;
coeff = 1/(k*A);
figure(3)
plot(xm(:,1)*sqrt(9.81/286.6), xm(:,5+1)*coeff,line_color);
%2
hold on;
amp = 9.687e-003;
ang = 105.750;
real = amp*cos(-w*xm(:,1)+ang*pi/180);
plot(xm(:,1)*sqrt(9.81/286.6), real*coeff, '.-k');
%
legend('Method in time domain','Result from frequency domain');
xlabel('t*sqrt(g/L)');
ylabel('Pitch/kA');
