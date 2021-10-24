% 物理学工程原理 第13组
clc;
clear;
% 程序说明
fprintf("光栅衍射相对强度曲线绘制 物原研讨小组 #13\n\n");
fprintf("模拟波长为 lambda 的单色光向垂直照射于光栅常数为 d，透光部分宽度为 a 的光栅时，\n");
fprintf("产生的衍射条纹的光强度曲线。\n--------------------\n\n");
% 输入必要的数据
fprintf("请输入光栅常数的倒数 1/d（单位：线/毫米）：\n");
d = input("1/d = ");
d_nm = (1 * 1000 * 1000) / d;
fprintf("\n请输入线间透光部分的宽度 a（单位：微米）：\n");
a = input("a = ");
a_nm = a * 1000;
% 判断a是否小于b
if (1000 / d) / 2 < a
  fprintf("\na应小于b！\n");
  return;
end
clear a d;
% 光的波长
fprintf("\n请输入入射光波长 lambda（单位：纳米）：\n");
lambda_in = input("lambda = ");
% 光栅缝数，绘图用
fprintf("\n请输入透射光栅总缝数 N：\n");
N = input("N = ");
% 计算 mu 和 beta
sin_theta = (-1: 0.001: 1);
mu = ((pi * a_nm) / lambda_in) * sin_theta;
beta = ((pi * d_nm) / lambda_in) * sin_theta;
clear lambda_in a_nm d_nm;
% 单缝衍射因子
single_slit = (sin(mu) ./ mu) .^ 2;
clear mu;
% 除零判断——一级主极大中心
for i = (1: size(single_slit, 2))
    if isnan(single_slit(i))
        single_slit(i) = 1;
    end
end
% 多缝干涉因子
mul_inter = (sin(N .* beta) ./ sin(beta)) .^ 2;
clear beta;
% 除零判断——一级主极大中心
for i = (1: size(mul_inter, 2))
    if isnan(mul_inter(i))
        mul_inter(i) = N ^ 2;
    end
end
clear i;
% 进行叠加
grating_func = single_slit .* mul_inter;
% 绘图
% 单缝衍射因子
subplot(2, 2, 1);
plot(sin_theta, single_slit);
xlabel('$$ \sin{\theta} $$', 'Interpreter', 'LaTeX');
ylabel('$$ \frac{\sin{\mu}}{\mu} $$', 'Interpreter', 'LaTeX');
title('单缝衍射因子相对强度');
% 多缝干涉因子
subplot(2, 2, 2);
plot(sin_theta, mul_inter);
xlabel('$$ \sin{\theta} $$', 'Interpreter', 'LaTeX');
ylabel('$$  \frac{\sin{N \beta}}{\sin{\beta}} $$', 'Interpreter', 'LaTeX');
title('多缝干涉因子相对强度');
% 最终光栅相对强度图像
subplot(2, 2, 3: 4);
plot(sin_theta, grating_func);
xlabel('$$ \sin{\theta} $$', 'Interpreter', 'LaTeX');
title('光栅衍射相对强度');
% 绘制条纹灰度图
x = ones(1, size(grating_func, 2));
% 一条线的灰度
x_line = x .* (grating_func ./ (N ^ 2));
clear x;
% 纵向复制
x_rep = repmat(x_line, ceil(size(grating_func, 2) * 3 / 4), 1);
clear x_line;
% 灰度转换
gray_img = mat2gray(x_rep);
% 为方便观察，亮度通过gamma曲线进行修正
gray_img = imadjust(gray_img, [0, 1], [0, 1], 0.5);
% 新窗口绘制灰度图
figure(2);
imshow(gray_img);
title('灰度图');
fprintf("绘图完毕！\n");
