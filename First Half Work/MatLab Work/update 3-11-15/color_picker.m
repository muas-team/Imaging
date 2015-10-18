function [ colors ] = color_picker( hue, sat, val)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
% I is the hue band of an hsv image

h = histogram(hue,[0,1*10^-10,0.01,0.125,0.3,0.6,0.75,0.9,1]);
counth = histcounts(hue,[0,1*10^-10,0.01,0.125,0.3,0.6,0.75,0.9,1]);

s = histogram(sat,[0,1*10^-3,1]);
counts = histcounts(sat,[0,1*10^-3,1]);

v = histogram(val,[0,0.1,0.8,1]);
countv = histcounts(val,[0,0.1,0.8,1]);

maxh = max(counth);
maxs = max(counts);
maxv = max(countv);

if (counth(2) == maxh)
    colors = 'Background = Red';
elseif (counth(3) == maxh)
    colors = 'Background = Orange';
elseif (counth(4) == maxh)
    colors = 'Background = Yellow';
elseif (counth(5) == maxh)
    colors = 'Background = Green';
elseif (counth(6) == maxh)
    colors = 'Background = Blue';
elseif (counth(7) == maxh)
    colors = 'Background = Purple';
elseif (countv(1) == maxv)
    colors = 'Background = Black';
elseif (countv(3) == maxv)
    colors = 'Background = White';
else
end

