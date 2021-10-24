clc;
clear;
t = (-4.5: 0.001: 5.5);
t1 = (-4.499: 0.001: 5.5);
x = [ones(1, 1000), zeros(1, 1000)];
x = [x, x, x, x, x];
subplot(2, 2, [1, 3]);
plot(t1, x, 'linewidth', 1.5);
axis([-4.5, 5.5, -0.5, 1.5]);
c0 = 0.5;
N = 10;
f1 = c0 * ones(1, length(1));
for n = 1: N
    f1 = f1 + cos(pi * n * t) * sinc(n / 2);
end
subplot(2, 2, 2);
plot(t, f1, 'r', 'linewidth', 1.5);
axis([-4.5, 5.5, -0.5, 1.5]);
title('N = 10');
N = 20;
f1 = c0 * ones(1, length(1));
for n = 1: N
    f1 = f1 + cos(pi * n * t) * sinc(n / 2);
end
subplot(2, 2, 4);
plot(t, f1, 'r', 'linewidth', 1.5);
axis([-4.5, 5.5, -0.5, 1.5]);
title('N = 20');
