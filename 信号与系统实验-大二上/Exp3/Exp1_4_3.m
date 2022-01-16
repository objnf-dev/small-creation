clc;
clear;

n = 0: 40;

f_1 = 1.5 * sin(2 * pi * 0.1 * n);
f_2 = sin(pi * 0.2 * n);
f_3 = 1.2 * cos (2 * pi * 0.1 * n);

f_1 = f_1(1: 40);
f_2 = f_2(1: 40);
f_3 = f_3(1: 40);

f_conv1 = conv(f_1, (f_2 + f_3));
f_conv2 = conv(f_1, f_2) + conv(f_1, f_3);

f_conv1 = f_conv1(1: 40);
f_conv2 = f_conv2(1: 40);

fd = f_conv1 - f_conv2;

subplot(3, 1, 1);
stem(f_conv1);
axis([0, 40, -30, 30]);
xlabel("Ê±¼äÐòºÅ n");
ylabel("Õñ·ù");
title("conv(f_1, (f_2 + f_3))");
grid;

subplot(3, 1, 2);
stem(f_conv2);
axis([0, 40, -30, 30]);
xlabel("Ê±¼äÐòºÅ n");
ylabel("Õñ·ù");
title("conv(f_1,  f_2) + conv(f_1, f_3)");
grid;

subplot(3, 1, 3);
stem(fd);
axis([0, 40, -30, 30]);
xlabel("Ê±¼äÐòºÅ n");
ylabel("Õñ·ù");
title("²îÐÅºÅÊä³ö");
grid;
