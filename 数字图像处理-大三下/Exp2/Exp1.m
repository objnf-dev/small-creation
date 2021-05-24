clc;
clear;

% 正方形
img = zeros(512, 512);
img(224: 288, 224: 288) = 255;
uint8(img);
figure;
subplot(2, 2, 1);
imshow(img);
title('正方形');

fft_img1 = fft2(img);
% abs的作用是求复数的模
fftabs_img1 = abs(fft_img1);
% fftshift将左上和右下侧的能量区域移动到中心
fftshift_img1 = fftshift(fftabs_img1);
subplot(2, 2, 2);
imagesc(fftshift_img1);
title('正方形的二维傅里叶');

% 长方形
img = zeros(512, 512);
img(192: 320, 224: 288) = 255;
uint8(img);
subplot(2, 2, 3);
imshow(img);
title('长方形');

fft_img2 = fft2(img);
fftabs_img2 = abs(fft_img2);
fftshift_img2 = fftshift(fftabs_img2);
subplot(2, 2, 4);
imagesc(fftshift_img2);
title('长方形的二维傅里叶');

figure;

% 竖条纹
img = zeros(512, 512);
for i = (1: 32: 512)
    img(1: 512, i: i + 16) = 255;
end
uint8(img);
subplot(2, 2, 1);
imshow(img);
title('竖向条纹');

fft_img3 = fft2(img);
fftabs_img3 = abs(fft_img3);
fftshift_img3 = fftshift(fftabs_img3);
subplot(2, 2, 2);
imagesc(fftshift_img3);
title('竖向条纹的二维傅里叶');

% 横条纹
img = zeros(512, 512);
for i = (1: 32: 512)
    img(i: i + 16, 1: 512) = 255;
end
uint8(img);
subplot(2, 2, 3);
imshow(img);
title('横向条纹');

fft_img4 = fft2(img);
fftabs_img4 = abs(fft_img4);
fftshift_img4 = fftshift(fftabs_img4);
subplot(2, 2, 4);
imagesc(fftshift_img4);
title('横向条纹的二维傅里叶');

figure;

% 圆形
img = zeros(512, 512);
for i = (192: 320)
    for j = (192: 320)
        if sqrt(abs(i - 256)^2 + abs(j - 256)^2) <= 64
            img(i, j) = 255;
        end
    end
end
uint8(img);
subplot(1, 2, 1);
imshow(img);
title('圆形');

fft_img5 = fft2(img);
fftabs_img5 = abs(fft_img5);
fftshift_img5 = fftshift(fftabs_img5);
subplot(1, 2, 2);
imagesc(fftshift_img5);
title('圆形的二维傅里叶');
