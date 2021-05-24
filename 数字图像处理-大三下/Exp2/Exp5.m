clc;
clear;

%读取图像
img = imread('RGB.png');
img_gray = im2gray(img);
figure;
subplot(1, 2, 1);
imshow(img_gray);
title('灰度图');

img_dct = dct2(img_gray);
subplot(1, 2, 2);
imagesc(log(abs(img_dct)));
title('二维DCT');

%更换背景模糊的真实照片
img2 = imread('photo.jpg');
img2_gray = im2gray(img2);
figure;
subplot(1, 2, 1);
imshow(img2_gray);
title('另一张照片的灰度图');

img2_dct = dct2(img2_gray);
subplot(1, 2, 2);
imagesc(log(abs(img2_dct)));
title('另一张照片的二维DCT');
