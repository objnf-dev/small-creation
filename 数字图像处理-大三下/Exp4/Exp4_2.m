clear;
clc;

img = imread('RGB.png');
img = im2gray(img);

% 加入不同类型的噪声
img_salt = imnoise(img, 'salt & pepper', 0.01);
img_gauss = imnoise(img, 'gaussian', 0, 0.01);
figure;
subplot(2, 2, 1);
imshow(img);
title('原始灰度图');
subplot(2, 2, 2);
exp = edge(img, 'Canny');
imshow(exp);
title('Origin, Canny');
subplot(2, 2, 3);
imshow(img_salt);
title('salt & pepper');
subplot(2, 2, 4);
imshow(img_gauss);
title('gaussian');

% 尝试进行边缘检测
salt_1 = edge(img_salt, 'Canny');
salt_2 = edge(img_salt, 'Prewitt');
salt_3 = edge(img_salt, 'Roberts');
salt_4 = edge(img_salt, 'zerocross');

figure;
subplot(2, 2, 1);
imshow(salt_1);
title('salt & pepper, Canny');
subplot(2, 2, 2);
imshow(salt_2);
title('salt & pepper, Prewitt');
subplot(2, 2, 3);
imshow(salt_3);
title('salt & pepper, Roberts');
subplot(2, 2, 4);
imshow(salt_4);
title('salt & pepper, zerocross');

gauss_1 = edge(img_gauss, 'Canny');
gauss_2 = edge(img_gauss, 'Prewitt');
gauss_3 = edge(img_gauss, 'Roberts');
gauss_4 = edge(img_gauss, 'zerocross');

figure;
subplot(2, 2, 1);
imshow(gauss_1);
title('gaussian, Canny');
subplot(2, 2, 2);
imshow(gauss_2);
title('gaussian, Prewitt');
subplot(2, 2, 3);
imshow(gauss_3);
title('gaussian, Roberts');
subplot(2, 2, 4);
imshow(gauss_4);
title('gaussian, zerocross');
