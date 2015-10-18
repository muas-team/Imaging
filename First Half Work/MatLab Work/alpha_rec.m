%% alpha_rec.m
%
% turns recog2.m into a function

%function [ out_txt, out_conf ] = alpha_rec( filename )

I = imread('OAGC.tif');
X = I(1:end, 1:end, 1:3);

I1 = rgb2gray(X);
I2 = imtophat(I1,strel('disk',30));
I3 = imadjust(I2, [0;0.4],[1;0]);
I4 = im2bw(I3);

out = ocr(I4 , 'TextLayout','Block');
out_txt = out.Text(1);
out_conf = out.CharacterConfidences(1);

%end

