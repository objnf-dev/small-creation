clc;
clear;
b = [1, 0, -1];
a = [1, 2 ,3 ,2];
zr = roots(b);
pr = roots(a);
plot(real(zr), imag(zr), 'go', real(pr), imag(pr), 'mx', 'markersize', 12, 'linewidth', 2);
grid;
legend('���', '����');
figure(2);
zplane(b, a);