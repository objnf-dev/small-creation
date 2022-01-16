clear;
clc;

rgb = imread('RGB.png');

% 分离各平面
rgb_r = rgb(:, :, 1);
rgb_g = rgb(:, :, 2);
rgb_b = rgb(:, :, 3);

% 算一下分辨率
[h, w] = size(rgb_r);

% 构造各个平面
Zero_plane = zeros(h, w);
R_plane = cat(3, rgb_r, Zero_plane, Zero_plane);
G_plane = cat(3, Zero_plane, rgb_g, Zero_plane);
B_plane = cat(3, Zero_plane, Zero_plane, rgb_b);

% 展示各平面
figure;
subplot(2, 2, 1);
imshow(R_plane);
title('R');
subplot(2, 2, 2);
imshow(G_plane);
title('G');
subplot(2, 2, 3);
imshow(B_plane);
title('B');
subplot(2, 2, 4);
imshow(rgb);
title('原图');

%计算YUV分量
%使用Analog YUV（YPbPr）
rgb_r = im2double(rgb_r);
rgb_g = im2double(rgb_g);
rgb_b = im2double(rgb_b);
M_yuv = [0.299, 0.587, 0.114; -0.168736, -0.331264, 0.5; 0.5, -0.418688, -0.081312];
[Y_plane, U_plane, V_plane] = deal(Zero_plane);

for i = (1: h)
    for j = (1: w)
        tmp = M_yuv * [rgb_r(i, j); rgb_g(i, j); rgb_b(i, j)];
        [Y_plane(i, j), U_plane(i, j), V_plane(i, j)] = deal(tmp(1, 1), tmp(2, 1), tmp(3, 1));
    end
end

%展示YPbPr
figure;
subplot(1, 3, 1);
imshow(Y_plane);
title('Y');
subplot(1, 3, 2);
imshow(U_plane);
title('Pb');
subplot(1, 3, 3);
imshow(V_plane);
title('Pr');

%计算YUV分量
%使用BT.601（YCbCr）
M_yuv = [65.481, 128.553, 24.966; -37.797, -74.203, 112; 112, -93.786, -18.214];
[Y_plane, U_plane, V_plane] = deal(Zero_plane);

for i = (1: h)
    for j = (1: w)
        tmp = M_yuv * [rgb_r(i, j); rgb_g(i, j); rgb_b(i, j)];
        [Y_plane(i, j), U_plane(i, j), V_plane(i, j)] = deal(tmp(1, 1) + 16, tmp(2, 1) + 128, tmp(3, 1) + 128);
    end
end

%展示YCbCr
figure;
subplot(1, 3, 1);
imshow(uint8(Y_plane));
title('Y');
subplot(1, 3, 2);
imshow(uint8(U_plane));
title('Cb');
subplot(1, 3, 3);
imshow(uint8(V_plane));
title('Cr');

