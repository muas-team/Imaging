% Create templates
% Read images
TRI=imread('shapes\TRI.bmp');STA=imread('shapes\STA.bmp');
CIR=imread('shapes\CIR.bmp');REC=imread('shapes\REC.bmp');
% Trim images
TRI=clip_shape(TRI);CIR=clip_shape(CIR);STA=clip_shape(STA);
% Resize to 42*24 resolution
TRI=imresize(TRI,[42 24]);CIR=imresize(CIR,[42 24]);
STA=imresize(STA,[42 24]);
% Stored in the database
letter=[TRI STA CIR REC];
character=letter;
templates=mat2cell(character,42,[24 24 24 24]);
save ('templates','templates')