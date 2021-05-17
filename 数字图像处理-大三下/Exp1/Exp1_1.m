clc;
clear;
%读取各文件
Gray = imread('test_suit/gray_512.bmp');
RGB_bmp = imread('test_suit/RGB24.BMP');
RGB_1080 = imread('test_suit/RGB1080.png');
[RGB_transp, unused, transp] = imread('test_suit/RGBtransparent.png');
[Indexed, cmap] = imread('test_suit/Indexed256.png');
YUV = imread('test_suit/YUVhigh.jpg');
GIF = imread('test_suit/RGBdynamic.gif', 'frames', 'all');
size(GIF)
