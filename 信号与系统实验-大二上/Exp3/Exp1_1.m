clear;
clc;

num = [0.9, -0.45, 0.35, 0.002];
den = [1, 0.71, -0.46, -0.62];

t = (1: 1: 20);
delta = (t ~= 1) * 0 + (t == 1) * 1;
h = filter(num, den, delta);

stem(h);
