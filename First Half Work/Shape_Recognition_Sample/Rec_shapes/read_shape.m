function [letter vd]=read_shape(imagn)
% Compute correlation between two images  42*24 px
comp=[];
load templates
for n=1:4 %4->Number of shapes the database TEMPLATES
    sem=corr2(templates{1,n},imagn);
    comp=[comp sem];
end
comp=abs(comp);
vd=find(comp==max(comp));
%*-*-*-*-*-*-*-*-*-*-*-*-*-
if     vd==1
    letter='TRIANGLE';   
elseif vd==2
    letter='STAR';
elseif vd==3
    letter='CIRCLE';
else
    letter='RECTANGLE';
end

