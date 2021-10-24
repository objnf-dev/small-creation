clear;
clc;

N = 45;

num = [0.9, -0.45, 0.35, 0.002];
den = [1, 0.71, -0.46, -0.62];

y = impz(num, den, N);    % 从1开始

t = (1: 1: 45);
delta = (t ~= 1) * 0 + (t == 1) * 1;
yd = filter(num, den, delta);

d = yd - y';

subplot(3, 1, 1);
stem(y);
xlabel('时间序号');
ylabel('impz 振幅');
grid;

subplot(3, 1, 2);
stem(t, yd);
xlabel('时间序号');
ylabel('冲激定义 振幅');
grid;

subplot(3, 1, 3);
stem(t, d);
xlabel('时间序号');
ylabel('差函数 振幅');
grid;
