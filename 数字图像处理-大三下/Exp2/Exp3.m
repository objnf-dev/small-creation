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

for i = (1: 1080)
    for j = (1: 1920)
        if abs(img_dct(i, j)) < 10
            img_dct(i, j) = 0;
        end
    end
end
%语法糖：img_dct(abs(img_dct) < 10) = 0;
figure;
img_trans = idct2(img_dct);
% 需要转换数据结构
img_trans = uint8(img_trans);
subplot(1, 2, 1);
imshow(img_trans);
title('修改后的灰度图');
subplot(1, 2, 2);
imagesc(log(abs(img_dct)));
title('修改后的二维DCT');
