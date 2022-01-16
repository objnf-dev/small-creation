clc;
clear;

% 正方形
img = zeros(512, 512);
img(224: 288, 224: 288) = 255;
uint8(img);
figure;
subplot(2, 2, 1);
imshow(img);
title('原图像');

fft_img1 = fft2(img);
fftabs_img1 = abs(fft_img1);
fftshift_img1 = fftshift(fftabs_img1);
subplot(2, 2, 2);
imagesc(fftshift_img1);
title('原图像的二维傅里叶');

% 旋转与平移
delta_x = 50;
delta_y = 40;
trans = [1 0 delta_x; 0 1 delta_y; 0 0 1];
%先旋转再平移
img_rot = imrotate(img, 45, 'nearest');
img_change = zeros(512, 512);
for i = (1: 512)
    for j = (1: 512)
        pos = [i-256, j-256, 1];
        pos = trans * pos';
        pos = floor(pos');
        if pos(1) <= 0 || pos(1) > 512 || pos(2) <=0 || pos(2) > 512
            continue;
        end
        img_change(pos(1), pos(2)) = img_rot(i, j);
    end
end
subplot(2, 2, 3);
imshow(img_change);
title('旋转和平移后的图像');

fft_img2 = fft2(img_change);
fftabs_img2 = abs(fft_img2);
fftshift_img2 = fftshift(fftabs_img2);
subplot(2, 2, 4);
imagesc(fftshift_img2);
title('该图像的二维傅里叶');
