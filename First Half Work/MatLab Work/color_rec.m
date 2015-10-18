%% Color Recognition
%
% uses color_picker.m to display colors within an image

function [ colors ] = color_rec( filename )

X = imread(filename);
I = X(1:end, 1:end, 1:3);
I2 = rgb2hsv(I);

% figure
% imshow(X)
I2_1 = I2(:,:,1);
I2_2 = I2(:,:,2);
I2_3 = I2(:,:,3);

figure('Name','Histograms of Image Pixels')

subplot(2,2,1)
histogram(I2_1)
title('Auto-binned Hue')

subplot(2,2,2)
histogram(I2_1,[1*10^-10,0.01,0.125,0.3,0.6,0.75,0.9,1])
title('Hue Binned Based on Color Wheel')

subplot(2,2,3)
histogram(I2_2)
title('Saturation')

subplot(2,2,4)
histogram(I2_3)
title('Value')

a = color_picker(I2_1,I2_2,I2_3);
colors = [strcat('Background',': ',a(1));strcat('Shape Color',': ',a(2));strcat('Alphanumeric Color',': ', a(3))];
end

