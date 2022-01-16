clear;
clc;

img = imread('coins.png');

figure;
subplot(2, 1, 1);
imshow(img);
title('原始图像');
subplot(2, 1, 2);
imhist(img);
title('原始图像直方图');

% 二值化
[h, w] = size(img);
img_bin = false(h, w);
for i = (1: h)
    for j = (1: w)
        if img(i, j) >= 100
            img_bin(i, j) = true;
        end
    end
end

figure;
imshow(img_bin);
title('二值化后的图像');
