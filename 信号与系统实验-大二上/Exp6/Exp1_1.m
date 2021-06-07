% 计算离散时间傅里叶变换的频率样本
clc;
clear;
h_sig = [1, 2, 3, 4, 5, 6, 7, 8, 9];
w=0: 0.005: pi;
h = fft(h_sig, size(w, 2));
figure(1);
subplot(2, 1, 1)
plot(2 * w / pi, real(h));
axis([0, 1, -30, 50]);
grid;
title('实部');
xlabel('$$ \omega / \pi $$', 'Interpreter', 'LaTeX');
ylabel('振幅');
subplot(2, 1, 2)
plot(2 * w / pi, imag(h));
axis([0, 1, -40, 50]);
grid;
title('虚部');
xlabel('$$ \omega / \pi $$', 'Interpreter', 'LaTeX');
ylabel('振幅');
figure(2);
subplot(2, 1, 1);
plot(2 * w / pi, abs(h));
axis([0, 1, -30, 50]);
grid;
title('幅度谱');
xlabel('$$ \omega / \pi $$', 'Interpreter', 'LaTeX');
ylabel('振幅');
subplot(2, 1, 2);
plot(2 * w / pi, angle(h));
axis([0, 1, -10, 10]);
grid;
title('相位谱');
xlabel('$$ \omega / \pi $$', 'Interpreter', 'LaTeX');
ylabel('以弧度为单位的相位');
