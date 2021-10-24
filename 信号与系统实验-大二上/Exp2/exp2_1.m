clear;
clc;

n = (0: 40);
a = 2; b = -3; D = 10;

x = cos(2 * pi * 0.1 * n);
xd = [zeros(1, D), x];

num = [2.24, 2.49];
den = [1, -0.4];

y = filter(num, den, x);
yd = filter(num, den, xd);
d = y - yd(1+D: 41+D);    % 计算差值输出 d[n]

subplot(3, 1, 1);
stem(n, y);
ylabel('振幅');
title('输出 y[n]');
grid;

subplot(3, 1, 2);
stem(n, yd(1: 41));
ylabel('振幅');
title(['由于延时输入 x[n-', num2str(D), ']的输出']);
grid;

subplot(3, 1, 3)
stem(n, d);
ylabel('振幅');
title('差信号');
grid;
