%% Fence detection
%
% This is how you track fences
%
%%
% Create a cascade detector object.
fenceDetector = vision.CascadeObjectDetector();

% Read a video frame and run the detector.
% videoFileReader = vision.VideoFileReader('visionface.avi');
% videoFrame      = step(videoFileReader);
% bbox            = step(fenceDetector, videoFrame);
testIm = imread('test1.jpg');

bbox = step(fenceDetector, testIm);

% Draw the returned bounding box around the detected face.
videoOut = insertObjectAnnotation(videoFrame,'rectangle',bbox,'Face');
figure, imshow(videoOut), title('Detected face');