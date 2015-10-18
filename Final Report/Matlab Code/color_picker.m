function [ colors ] = color_picker( hue, sat, val)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
% I is the hue band of an hsv image

h = histogram(hue,[0,1*10^-10,0.01,0.125,0.3,0.6,0.75,0.9,1]);
counth = histcounts(hue,[0,1*10^-10,0.01,0.125,0.3,0.6,0.75,0.9,1]);
counth = [counth;1 2 3 4 5 6 7 8];
counth = counth.';
sorted_h = sortrows(counth);

s = histogram(sat,[0,1*10^-3,1]);
counts = histcounts(sat,[0,1*10^-3,1]);
counts = [counts;1 2];
counts = counts.';
sorted_s = sort(counts);

v = histogram(val,[0,0.1,0.8,1]);
countv = histcounts(val,[0,0.1,0.8,1]);
countv = [countv;1 2 3];
countv = countv.';
sorted_v = sort(countv);

maxh = counth(8);
maxs = counts(2);
maxv = countv(3);

chm = counth(6:8,2)
csm = counts(:,2);
cvm = countv(:,2);

colors = [];

for i = 1:3
    colors = strcat(colors, num2str(i),': ');
    if (chm(i) == 2)
        colors = strcat(colors,'Red');
    elseif (chm(i) == 3)
        colors = strcat(colors,'Orange');
    elseif (chm(i) == 4)
        colors = strcat(colors,'Yellow');
    elseif (chm(i) == 5)
        colors = strcat(colors,'Green');
    elseif (chm(i) == 6)
        colors = strcat(colors,'Blue');
    elseif (chm(i) == 7)
        colors = strcat(colors,'Purple');
    elseif (cvm(i) == 1)
        colors = strcat(colors,'Black');
    elseif (cvm(i) == 3)
        colors = strcat(colors,'White');
    end
    strcat(colors, ' ')
end
end

