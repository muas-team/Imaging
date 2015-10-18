%% Shape Distinctions
%
% This file takes in a color image, enhances the contrast, then makes it a
% binary image. It then uses this binary image to detect the border of the
% shape and then calculate the centroid and the distances from the centroid
% to compare to sample data in order to determine which shape it is an
% output that name. 

function [window] = shape_find(filename)
X = imread(filename);
I = X(1:end, 1:end, 1:3);
I2 = rgb2gray(I);
I2 = imadjust(I2, [0;1], [1;0]);
% figure
% imshow(I2)
I2 = im2bw(I2);
% I3 = bwconncomp(I2);

% Pulling out boundary points
window = figure('Name','Shape Recognition Progress');
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
distPlot2 = round(distPlot, -1);
distPlot = cast(distPlot2, 'like', distPlot);
subplot(2,2,3)
hold on
plot(distPlot)
% axis([0 length(boundary) 400 800])
hold off
title('Distance from Centroid to Edge')

% Showing the initial shape
subplot(2,2,1)
imshow(I);
title('Original Image')

% Shape Comparisons

[maxs locs] = findpeaks(distPlot2,'MinPeakDistance',cast(length(boundary)/12,'int16'));
subplot(2,2,4)
plot(locs, maxs, 'r+')
title('Corners')

end