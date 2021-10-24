clear;
clc;

img = imread('RGB.png');

% 简单低通滤波
lowpass_3 = ones(3, 3) ./ (3 * 3);
lowpass_9 = ones(9, 9) ./ (9 * 9);

% 简单高斯滤波
gauss_5_1 = fspecial('gaussian', 5, 1);
gauss_5_05 = fspecial('gaussian', 5, 0.5);
gauss_7_1 = fspecial('gaussian', 7, 1);

% 绘制滤波后的图像与频率响应
figure;
imshow(img);
title('原始图像');

figure;
subplot(2, 2, 1);
img_low3_corr = imfilter(img, lowpass_3);
imshow(img_low3_corr);
title('LowPass n=3');
subplot(2, 2, 2);
img_low3_conv = imfilter(img, lowpass_3, 'conv');
imshow(img_low3_conv);
title('LowPass n=3 conv');
subplot(2, 2, 3);
img_low9_corr = imfilter(img, lowpass_9);
imshow(img_low9_corr);
title('LowPass n=9');
subplot(2, 2, 4);
img_low9_conv = imfilter(img, lowpass_9, 'conv');
imshow(img_low9_conv);
title('LowPass n=9 conv');

figure;
subplot(2, 3, 1);
img_g_5_1_corr = imfilter(img, gauss_5_1);
imshow(img_g_5_1_corr);
title('Gaussian sigma=1 n=5');
subplot(2, 3, 4);
img_g_5_1_conv = imfilter(img, gauss_5_1, 'conv');
imshow(img_g_5_1_conv)
title('Gaussian sigma=1 n=5 conv');
subplot(2, 3, 2);
img_g_5_05_corr = imfilter(img, gauss_5_05);
imshow(img_g_5_05_corr);
title('Gaussian sigma=0.5 n=5');
subplot(2, 3, 5);
img_g_5_05_conv = imfilter(img, gauss_5_05, 'conv');
imshow(img_g_5_05_conv)
title('Gaussian sigma=0.5 n=5 conv');
subplot(2, 3, 3);
img_g_7_1_corr = imfilter(img, gauss_7_1);
imshow(img_g_7_1_corr);
title('Gaussian sigma=1 n=7');
subplot(2, 3, 6);
img_g_7_1_conv = imfilter(img, gauss_7_1, 'conv');
imshow(img_g_7_1_conv)
title('Gaussian sigma=1 n=7 conv');

% 频率响应
figure;
subplot(2, 3, 1);
freqz2([0]);
title('平直响应');
subplot(2, 3, 2);
freqz2(lowpass_3);
title('LowPass n=3');
subplot(2, 3, 3);
freqz2(lowpass_9);
title('LowPass n=9');
subplot(2, 3, 4);
freqz2(gauss_5_05);
title('Gaussian sigma=0.5 n=5');
subplot(2, 3, 5);
freqz2(gauss_5_1);
title('Gaussian sigma=1 n=5');
subplot(2, 3, 6);
freqz2(gauss_7_1);
title('Gaussian sigma=1 n=7');
