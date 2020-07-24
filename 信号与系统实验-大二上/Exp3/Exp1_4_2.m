clc;
clear;

n = 0: 40;

f_1 = 1.5 * sin(2 * pi * 0.1 * n);
f_2 = sin(pi * 0.2 * n);

f_conv1 = conv(f_1(1: 40), f_2(1: 40));
f_conv2 = conv(f_2(1: 40), f_1(1: 40));
fd = f_conv1(1: 40) - f_conv2(1: 40);

subplot(3, 1, 1);
stem(f_conv1(1: 40));
axis([0, 40, -20, 20]);
xlabel("时间序号 n");
ylabel("振幅");
title("conv(f_1, f_2)");
grid;

subplot(3, 1, 2);
stem(f_conv2(1: 40));
axis([0, 40, -20, 20]);
xlabel("时间序号 n");
ylabel("振幅");
title("conv(f_2, f_1)");
grid;

subplot(3, 1, 3);
stem(fd);
axis([0, 40, -20, 20]);
xlabel("时间序号 n");
ylabel("振幅");
title("差信号输出");
grid;
