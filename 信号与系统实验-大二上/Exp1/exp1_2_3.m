A = 0.25;
num = 1.2;
n = (0: 1: 20);
f = A * num .^ n;
stem(n, f);
