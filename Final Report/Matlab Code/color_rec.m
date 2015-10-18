%% Color Recognition

X = imread('ncsu_N.jpg');
I = X(1:end, 1:end, 1:3);
I2 = rgb2hsv(I);

imshow(X)
I1_1 = I(:,:,1); % red
I1_2 = I(:,:,2); % green
I1_3 = I(:,:,3); % blue
I2_1 = I2(:,:,1);
I2_2 = I2(:,:,2);
I2_3 = I2(:,:,3);

figure          % 1
histogram(I2_3)
title('value')

figure          % 2
subplot(2,1,1)
histogram(I2_1,[1*10^-10,0.01,0.125,0.3,0.6,0.75,0.9,1])
title('hue')

subplot(2,1,2)
histogram(I2_1)
title('hue')

figure          % 3
histogram(I2_2)
title('saturation')

I3 = ((0.3>I2_1) & (I2_1>0.125));
I3 = I3.*(1-I2_1);
figure          % 4
imshow(I3)

figure
a = color_picker(I2_1,I2_2,I2_3);
disp(a);
title('whyyyy')
close

