% for i = 1:6
%     filename = strcat('training',num2str(i),'.jpg');
%     X = imread(filename);
%     I = rgb2gray(X);
%     I = imadjust(I, [0;1], [1;0]);
%     X = im2bw(I);
%     subplot(3,2,i);
%     imshow(X)
%     template_detection(:,:,i) = X;
% end


for i = 1:5
    filename = strcat('test',num2str(i),'.jpg');
    X = imread(filename);
    X = rgb2gray(X);
    [Gmag, Gdir] = imgradient(X,'prewitt');
    fence = (Gmag > 0.3*(max(max(Gmag))));
    subplot(3,2,i)
    imshow(fence); % Gmag./max(max(Gmag))
end





