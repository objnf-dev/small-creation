clc;
clear;

n = (0: 40);
d = 5;
delta = (n ~= d) * 0 + (n == d) * 1;

f = 1.5 * sin(2 * pi * 0.2 * n);
f_conv = conv(f, delta);
f_conv = f_conv(1: 40);

xd = [zeros(1, d), f];
f_delay = filter(1, 1, xd);
f_delay = f_delay(1: 40);
fd = f_conv - f_delay;

subplot(3, 1, 1);
stem(f_conv);
axis([0, 40, -5, 5]);
xlabel("时间序号 n");
ylabel("振幅");
title("f_conv");
grid;

subplot(3, 1, 2);
stem(f_conv);
axis([0, 40, -5, 5]);
xlabel("时间序号 n");
ylabel("振幅");
title("f_delay");
grid;

subplot(3, 1, 3);
stem(fd);
axis([0, 40, -5, 5]);
xlabel("时间序号 n");
ylabel("振幅");
title("差信号输出");
grid;
