% 计算离散时间傅里叶变换的频率样本
clc;
clear;
w = -4 * pi: 8 * pi / 511: 4 * pi;
num = (2, 1);
den = (1, -0.6);
h = freqz(num, den, w);
subplot(2,1,1)
plot(w / pi, real(h));
grid;
title('实部');
xlabel('\omega \pi');
ylabel(‘振幅’);
subplot(2,1,2)
plot(w/pi, imag(h)); grid;
title(‘虚部’)
xlabel(‘omega/\pi’);
ylabel(‘振幅’);
figure;
subplot(2,1,1)
plot(w/pi, abs(h)); grid;
title(‘幅度谱’)
xlabel(‘omega/\pi’);
ylabel(‘振幅’);
subplot(2,1,2)
plot(w/pi, angle (h)); grid;
title(‘相位谱’)
xlabel(‘omega/\pi’);
ylabel(‘以弧度为单位的相位’);
