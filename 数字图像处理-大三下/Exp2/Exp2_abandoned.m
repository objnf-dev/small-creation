clc;
clear;

% 正方形
img = zeros(512, 512);
img(224: 288, 224: 288) = 255;
uint8(img);
figure;
subplot(2, 2, 1);
imshow(img);

fft_img1 = fft2(img);
fftabs_img1 = abs(fft_img1);
fftshift_img1 = fftshift(fftabs_img1);
subplot(2, 2, 2);
imagesc(fftshift_img1);

% 旋转与平移
delta_x = 50;
delta_y = 40;
angle = pi/4;
img_change = zeros(512, 512);
% 齐次矩阵
trans = [1 0 delta_x; 0 1 delta_y; 0 0 1];
rot = [cos(angle) -sin(angle) 0; sin(angle) cos(angle) 0; 0 0 1];
%先旋转再平移
for i = (1: 512)
    for j = (1: 512)
        pos = [i-256, j-256, 1];
        pos = rot * pos';
        pos = floor(pos');
        pos = [pos(1) + 256 pos(2) + 256 1];
        if pos(1) <= 0 || pos(1) > 512 || pos(2) <=0 || pos(2) > 512
            continue;
        end
        img_change(pos(1), pos(2)) = img(i, j);
    end
end
subplot(2, 2, 3);
imshow(img_change);


