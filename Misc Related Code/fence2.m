% Load training and test data using imageSet.
trainingDir   = fullfile('ENEE499', 'Fence Detection','TrainingImages');
testingDir = fullfile('ENEE499', 'Fence Detection','TestImages');

% imageSet recursively scans the directory tree containing the images.
trainingSet = imageSet(trainingDir, 'recursive');
testSet     = imageSet(testingDir, 'recursive');

[hog_2x2, vis2x2] = extractHOGFeatures(img,'CellSize',[2 2]);
cellSize = [2 2];
hogFeatureSize = length(hog_2x2);

% The trainingSet is an array of 10 imageSet objects: one for each digit.
% Loop over the trainingSet and extract HOG features from each image. A
% similar procedure will be used to extract features from the testSet.

trainingFeatures = [];
trainingLabels   = [];

for digit = 1:numel(trainingSet)

    numImages = trainingSet(digit).Count;
    features  = zeros(numImages, hogFeatureSize, 'single');

    for i = 1:numImages

        img = read(trainingSet(digit), i);

        % Apply pre-processing steps
        lvl = graythresh(img);
        img = im2bw(img, lvl);

        features(i, :) = extractHOGFeatures(img, 'CellSize', cellSize);
    end

    % Use the imageSet Description as the training labels. The labels are
    % the digits themselves, e.g. '0', '1', '2', etc.
    labels = repmat(trainingSet(digit).Description, numImages, 1);

    trainingFeatures = [trainingFeatures; features];   %#ok<AGROW>
    trainingLabels   = [trainingLabels;   labels  ];   %#ok<AGROW>

end

% fitcecoc uses SVM learners and a 'One-vs-One' encoding scheme.
classifier = fitcecoc(trainingFeatures, trainingLabels);




