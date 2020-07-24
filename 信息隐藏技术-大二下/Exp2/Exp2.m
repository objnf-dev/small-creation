function Exp2()
    clc;
    clear;

    originRGB = imread('carrier.png');
    origin = rgb2gray(originRGB);
    imwrite(origin, 'gray.png');
    
    embedRGB = imread('embedded.png');
    embed = rgb2gray(embedRGB);
    embedThresh = graythresh(embed);
    embed = imbinarize(embed, embedThresh);
    imwrite(embed, 'binary.png');
    
    clear originRGB;
    clear embedRGB;
    clear embedThresh;
    
    embed = ImageResize(embed, 'binary', 64);
    origin_dct = ImageDCT(origin);
    origin_dct = ImageSeparate(origin_dct);
    
    [pic_embed, dct_pos] = WatermarkEmbed(embed, origin_dct);
    pic_embed = uint8(ImageInverseDCT(pic_embed));
    imwrite(pic_embed, 'watermarked.png');
    dlmwrite('pos.txt', dct_pos);
    
    pic_dec = WatermarkExtract(pic_embed, dct_pos);
    imwrite(pic_dec, 'extracted.png');
    
    psnr_val = psnr(pic_embed, origin);
    fprintf("PSNR value is: %f\n", psnr_val);
    
    false_rate = WatermarkSimilarity(embed, pic_dec);
    fprintf("False rate is: %f\n", 1 - false_rate);
    
    gauss = imgaussfilt(pic_embed);
    pic_dec2 = WatermarkExtract(gauss, dct_pos);
    false_rate2 = WatermarkSimilarity(embed, pic_dec2);
    fprintf("False rate 2 is: %f\n", 1 - false_rate2);
end

function pic = ImageResize(pic, picName, length)
    pic = imresize(pic, [length, length]);
    imwrite(pic, picName + " _" + string(length) + '.png');
end

function pic_dct = ImageDCT(pic)
    pic = double(pic);
    fun = @(blk_struct) dct2(blk_struct.data);
    pic_dct = blockproc(pic, [8, 8], fun);
end

function pic_rdct = ImageInverseDCT(pic)
    fun = @(blk_struct) idct2(blk_struct.data);
    pic_rdct = blockproc(pic, [8, 8], fun);
end

function pic_sep = ImageSeparate(pic)
    pic_sep = mat2cell(pic, repelem(8, 64), repelem(8,64));
end

function [pic_embed, pos] = WatermarkEmbed(emb, pic)
    pos = [];
    for row = 1: 64
        for col = 1: 64
            [u1, v1, u2, v2] = FindPoint(pic{row, col});
            pos = [pos; u1, v1, u2, v2;];
            if emb(row, col) == 1
                if abs(pic{row, col}(u1, v1) - pic{row, col}(u2, v2)) <= 10
                    pic{row, col}(u1, v1) = pic{row, col}(u1, v1) - 9;
                    pic{row, col}(u2, v2) = pic{row, col}(u2, v2) + 9;
                end
            else
                if abs(pic{row, col}(u1, v1) - pic{row, col}(u2, v2)) >= 10
                    tmp = pic{row, col}(u1, v1) + pic{row, col}(u2, v2);
                    tmp = tmp / 2;
                    pic{row, col}(u1, v1) = tmp;
                    pic{row, col}(u2, v2) = tmp;
                    clear tmp;
                end
            end
        end
    end
    
    pic_embed = cell2mat(pic);
end

function [u1, v1, u2, v2] = FindPoint(pic_block)
    pic_block = reshape(pic_block', 1, []);
    [~, pos] = sort(pic_block);
    tmp1 = floor(pos(32) / 8);
    tmp2 = rem(pos(32), 8);
    if tmp2 == 0
        u1 = tmp1;
        v1 = 8;
    else
        u1 = tmp1 + 1;
        v1 = tmp2 + 1;
    end
    tmp1 = floor(pos(33) / 8);
    tmp2 = rem(pos(33), 8);
    if tmp2 == 0
        u2 = tmp1;
        v2 = 8;
    else
        u2 = tmp1 + 1;
        v2 = tmp2 + 1;
    end
end

function pic_dec = WatermarkExtract(pic, pos)
    pic_dec = zeros(64, 64);
    pic = ImageDCT(pic);
    pic = ImageSeparate(pic);
    pos_row = 1;
    for row = 1: 64
        for col = 1: 64
            [u1, v1, u2, v2] = deal(pos(pos_row, 1), pos(pos_row, 2), pos(pos_row, 3), pos(pos_row, 4));
            if abs(pic{row, col}(u1, v1) - pic{row, col}(u2, v2)) >= 10
                pic_dec(row, col) = 1;
            end
            pos_row = pos_row + 1;
        end
    end
end

function res = WatermarkSimilarity(pic1, pic2)
    max_pixel = 64 * 64;
    currect_pixel = 0;
    
    for row = 1: 64
        for col = 1:64
            if pic1(row, col) == pic2(row, col)
                currect_pixel = currect_pixel + 1;
            end
        end
    end
    
    res = currect_pixel / max_pixel;
end
