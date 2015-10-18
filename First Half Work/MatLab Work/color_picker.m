function [ colors ] = color_picker( hue, sat, val)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
% I is the hue band of an hsv image

counth = histcounts(hue,[0,1*10^-10,0.01,0.125,0.3,0.6,0.75,0.9,1]);
counth = [counth;1 2 3 4 5 6 7 8];
counth = counth.';
sorted_h = sortrows(counth);

countv = histcounts(val,[0,0.1,0.8,1]);
countv = [countv;1 2 3];
countv = countv.';
sorted_v = sort(countv);

chm = sorted_h(6:8,2);
cvm = sorted_v(:,2);

colors = {'';'';''};

for i = 1:3
    if (chm(4-i) == 2)
        colors(i) = {'Red'};
    elseif (chm(4-i) == 3)
        colors(i) = {'Orange'};
    elseif (chm(4-i) == 4)
        colors(i) = {'Yellow'};
    elseif (chm(4-i) == 5)
        colors(i) = {'Green'};
    elseif (chm(4-i) == 6)
        colors(i) = {'Blue'};
    elseif (chm(4-i) == 7)
        colors(i) = {'Purple'};
    elseif (cvm(4-i) == 1)
        colors(i) = {'Black'};
    elseif (cvm(4-i) == 3)
        colors(i) = {'White'};
    end
end
end

