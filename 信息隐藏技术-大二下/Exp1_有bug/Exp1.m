function Exp1()
    % Initialize
    clear;
    clc;
    
    % Must be ASCII-encoded
    message = fileread('enc100.txt');
    raw = imread('test.png');
    watermarked = 'out100.png';

    % Grayscale Image
    carrier = rgb2gray(raw);
    imwrite(carrier, 'carrier.png');
    clear raw;
    
    % 30% capacity: 154*154/8 `= 2964 chars
    % 60% capacity: 307*307 `= 11781 chars
    % 100% capacity: 511*511/8 `= 32640 chars
    lsb_encode(carrier, message, watermarked);
    lsb_decode(watermarked);
    
    proceeded = imread(watermarked);
    picture_quality(carrier, proceeded);
end

function lsb_encode(gray_img, msg_data, filename)
    % Text Preprocessing
    msg_b64 = matlab.net.base64encode(msg_data);
    clear message;
    % fprintf('Watermarked text length: %d\n', msg_len);
    
    % Change message to binary
    msg_b64_bin = dec2bin(msg_b64, 8);
    msg_b64_bin = uint8(reshape(msg_b64_bin.'-'0', 1, []));
    clear msg_b64;
    
    % Calculate size
    msg_len = size(msg_b64_bin, 2);
    fprintf('Watermarked binary size: %d\n', msg_len);
    msg_len_sqrt = ceil(sqrt(msg_len));
    msg_len_num = uint8(reshape(dec2bin(msg_len_sqrt, 10).'-'0', [], 1));
    
    %Paddling
    if msg_len < msg_len_sqrt^2
        paddle = msg_len_sqrt^2 - msg_len;
        for i = 1: paddle
            msg_b64_bin = [msg_b64_bin, 0];
        end
    end
    
    % Embedding Size
    for i = 1:10
        gray_img(1, i) = bitset(gray_img(1, i), 1, msg_len_num(i));
    end
    
    % Embedding Content
    k = 1;
    for i = 2:(msg_len_sqrt + 1)
        for j = 1:msg_len_sqrt
            gray_img(i, j) = bitset(gray_img(i, j), 1, msg_b64_bin(k));
            k = k + 1;
        end
    end
    
    % Write Image
    fprintf('Watermarking succeeded.\n');
    imwrite(gray_img, filename);
end

function lsb_decode(filename)
    image = imread(filename);
    size = [];
    for i = 1: 10
        size = [size, bitget(image(1, i), 1)];
    end
    size = cast(bi2de(size, 'left-msb'), 'uint32');
    char_num = floor(size^2 / 8);
    
    data=[];
    for i = 2: (size + 1)
        for j = 1: size
            data = [data, bitget(image(i, j), 1)];
        end
    end
    data = data(1: char_num * 8);
    data = reshape(data'.'+'0', 8, []);
    
    data_chr = [];
    for i = 1: char_num
        tmp = '';
        for j = 1: 8
            tmp = [tmp, char(data(j, i))];
        end
        data_chr = [data_chr; tmp];
    end
    data_chr = uint8(bin2dec(data_chr))';
    data_chr = char(data_chr);
    data_chr = matlab.net.base64decode(data_chr);
    data_chr = char(data_chr);
    
    % fprintf('Plaintext:\n%s\n', data_chr);
end

function picture_quality(imgA, imgB)
    [peaksnr, ~] = psnr(imgA, imgB);
    fprintf('PSNR value: %f\n', peaksnr);
end
