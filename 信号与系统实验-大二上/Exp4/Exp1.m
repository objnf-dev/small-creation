clc;
clear;
t = (0: 0.0001: 0.25);          % 0-0.25 时间间隔为 0.0001
y = zeros(10, max(size(t)));  % 10*629（t的长度）的矩阵
x = zeros(10, max(size(t)));
for k = (1: 2: 9)             % 奇次谐波 1, 3, 5, 7, 9
    x1 = ((4 * 3) / pi) * sin(k * 100 * t) / k;      % 各次谐波正弦分量
    x(k,:) = x(k,:) + x1;     % x第k(1, 3, 5, 7, 9)行存放k次谐波的629个值
    y((k + 1) / 2,:) = x(k,:); % 矩阵非零行向量移至第1-5行
end
figure(1);
subplot(5, 1, 1);
plot(t, y(1, :));
grid;
title('第一项谐波分量');
subplot(5, 1, 2);
plot(t, y(2, :));
grid;
title('第二项谐波分量');
subplot(5, 1, 3);
plot(t, y(3, :));
grid;
title('第三项谐波分量');
subplot(5, 1, 4);
plot(t, y(4, :));
grid;
title('第四项谐波分量');
subplot(5, 1, 5);
plot(t, y(5, :));
grid;
title('第五项谐波分量');
figure(2);
subplot(2, 1, 1);
plot(t, y(1: 5,:));           % 绘制矩阵中1-5行随时间变化的波形
grid;
title('二维叠加图');
halft = ceil(length(t) / 2);  % 行向量长度减半（由于对称前后段一致）
subplot(2, 1, 2);             % 绘制三维图形：矩阵y中全部行向量的一半
mesh(t(1: halft), (1: 10), y(:, 1: halft));
title('三维图像');
