%% shape_rec.m
%
% turns attempt1.m into a function
% FOLLOW UP INTO POLAR

% function [ out_txt, out_conf ] = shape_rec( filename )

%X = imread(filename);
X = imread('OAGC.tif');
I = X(1:end, 1:end, 1:3);
I2 = rgb2gray(I);
I2 = imadjust(I2, [0;1], [1;0]);

I2 = im2bw(I2);

% Pulling out boundary points
figure
[B,L,N,A] = bwboundaries(I2);
stat = regionprops(I2, 'Centroid');
cent = stat.Centroid;
boundary = B{1};
subplot(2,2,2)
hold on
plot(boundary(:,2), boundary(:,1), 'b', 'LineWidth', 1)
plot(cent(1),cent(2), 'g+')
axis([0 length(I(1,:))/3 0 length(I(:,1))])
hold off
title('Edges')

% Finding Distances from Centroid
distPlot = [];
for i = 1:length(boundary)
%     distPlot = [distPlot cast(sqrt((cent(1)-boundary(i,1))^2 + (cent(2)-boundary(i,2))^2),'int32')];
    distPlot = [distPlot sqrt((cent(1)-boundary(i,1))^2 + (cent(2)-boundary(i,2))^2)]; 
    % does not cast data to integer for use later with findpeaks
end

[maxs locs] = findpeaks(double(cast(distPlot,'int16')),'MinPeakDistance',cast(length(boundary)/20,'int16'));

I_hsv = rgb2hsv(I);
Ih1 = I_hsv(:,:,1);
Ih2 = I_hsv(:,:,2);
Ih3 = I_hsv(:,:,3);
figure
a = color_picker(Ih1,Ih2,Ih3)
histogram(Ih1,[0,1*10^-10,0.01,0.125,0.3,0.6,0.75,0.9,1])
figure
histogram(Ih2,[0,1*10^-3,1])

I3 = (Ih2 <= 1 & Ih2 > 1*10^-3);
I3 = I3.*(Ih2);
figure
imshow(I3)

% end