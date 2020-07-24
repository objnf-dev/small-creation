A = 2;
w0 = 2 * pi;
phi = pi / 2;
n = (0:50);
f = 0.08;
arg = w0 * f * n + phi;
y = A * sin(arg);
stem(n, y);
axis([0, 40, -2, 2]);
grid;
title('正弦序列');
xlabel('时间序号 n');
ylabel('振幅');
