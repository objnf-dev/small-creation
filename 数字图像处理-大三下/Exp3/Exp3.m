function Exp3()
    clc;
    clear;
    
    rgb = imread('RGB.png');
    yuv = imread('YUV444.jpg');

    figure;
    subplot(2, 2, [1, 2]);
    imshow(rgb);
    title('原始彩色图像1')
    gray_1 = im2gray(rgb);
    subplot(2, 2, 3);
    imshow(gray_1);
    title('灰度图像1');
    subplot(2, 2, 4);
    imhist(gray_1);
    title('灰度图像1的直方图');

    figure;
    subplot(2, 2, [1, 2]);
    imshow(yuv);
    title('原始彩色图像2');
    gray_2 = im2gray(yuv);
    subplot(2, 2, 3);
    imshow(gray_2);
    title('灰度图像2');
    subplot(2, 2, 4);
    imhist(gray_2);
    title('灰度图像2的直方图');

    % 以图像1为例
    figure;
    % 线性映射
    [h, w] = size(gray_1);
    gray_l = zeros(h, w);
    for i = (1: h)
        for j = (1: w)
            gray_l(i, j) = LinearTransform(gray_1(i, j));
        end
    end
    gray_l = uint8(gray_l);
    subplot(2, 2, 1);
    imshow(gray_l);
    title('线性拉伸后的图像');
    subplot(2, 2, 2);
    imhist(gray_l);
    title('线性拉伸后的直方图');
    
    % 计算颜色概率
    [hist_count, ~] = imhist(gray_l);
    hist_count = hist_count ./ (h * w);
    subplot(2, 2, 3);
    plot(hist_count);
    axis([0, 255, 0, 0.03]);
    title('各颜色概率');
    
    % 计算CDF
    [hist_h, ~] = size(hist_count);
    cdf = zeros(hist_h, 1);
    accu = 0;
    for i = (1: hist_h)
        accu = accu + hist_count(i, 1);
        cdf(i, 1) = accu;
    end
    
    subplot(2, 2, 4);
    plot(cdf);
    axis([0, 255, 0, 1]);
    title('各颜色累积概率');
    
    % 利用cdf将映射后的图像还原
    figure;
    subplot(2, 2, 1);
    gray_h = histeq(gray_l);
    imshow(gray_h);
    title('均衡后的图像');
    subplot(2, 2, 2);
    imhist(gray_h);
    title('均衡后的直方图');
    subplot(2, 2, 3);
    imshow(gray_l);
    title('原始灰度图');
    subplot(2, 2, 4);
    imhist(gray_l);
    title('原始直方图');
    
end

function ret = LinearTransform(val)
    ret = (220 - 32) / 255 * val + 32;
end
