%% outputtxt.m
%
% Outputs the text from the shape recognition and color recognition into a
% text file

fileIDs = {'OAGC.tif';'t.tif';'ncsu_N.jpg'};

t_ID = [1:numel(fileIDs)];
shapes = {'square';'circle';'triangle';'hexagon';'pentagon';'cross';'star';'square'};
colors = {'red';'orange';'yellow';'green';'blue';'purple';'black';'white'};
alphas = [];
confs = []; % confidence value for that letter

for i = t_ID
    ID = char(fileIDs(i));
    [txt conf] = alpha_rec(ID);
    alphas = [alphas;txt];
    confs = [confs;conf];
end
targID = t_ID.';
T = table(targID,alphas,confs);
writetable(T,'ENEE.txt','Delimiter','\t','WriteRowNames',true);