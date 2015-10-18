function varargout = rec_shapes(varargin)
% Author: Diego Barragán.
% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @rec_shapes_OpeningFcn, ...
    'gui_OutputFcn',  @rec_shapes_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end
if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT
% -----------------------------------------------------------------------
function rec_shapes_OpeningFcn(hObject, eventdata, handles, varargin)
% Center GUI
movegui(hObject,'center')
handles.output = hObject;
% Handles of image
handles.rgb    = [];
set(handles.video_cam,'XTick',[ ],'YTick',[ ])
guidata(hObject, handles);

% -----------------------------------------------------------------------
% --- Outputs from this function are returned to the command line.
function varargout = rec_shapes_OutputFcn(hObject, eventdata, handles)
varargout{1} = handles.output;
% --- FUNCTION IMAGE CAPTURE
function captura_Callback(hObject, eventdata, handles)
try
    % Acquire webcam image
    handles.rgb = getsnapshot(handles.vidobj);
    if handles.es_web_ext==0
        handles.rgb=ycbcr2rgb(handles.rgb);
    end
catch
    % If the camera is not connected, take default image.
    handles.rgb = imread('profile.jpg');        
end
% Update handles structure
guidata(hObject, handles);
% Show captured image
image(handles.rgb,'Parent',handles.fotografia);
axes(handles.fotografia)
% Delete axes
axis off
%------------------------------------------------------------------------------------------------------------------------
% PREPROCESSING FUNCTION
function pre_proc_Callback(hObject, eventdata, handles)
% Call acquired image
img = handles.rgb;        
% Convert to Grayscale
gris= rgb2gray(img);      
% Calculate the threshold
umb = graythresh(gris);   
% Convert to binary
bw  = im2bw(gris,umb);    
% Morphological operation to remove holes
bw  = bwmorph(~bw,'open');
% Remove noise on image
bw  = bwmorph(bw,'close');
% Fill holes
bw  = imfill(bw,'holes'); 
% Select axes to plot
axes(handles.fotografia)  
% Show the binary image has been preprocessed
imshow(~bw)               
% Store the image on a handle to move it to another function
handles.bw=~bw;           
guidata(hObject,handles)  
%------------------------------------------------------------------------------------------------------------------------
% --- SEARCH OBJECTS IN THE PICTURE
function find_obj_Callback(hObject, eventdata, handles)
% Call the preprocessed image
bw      = handles.bw;   
% Count objects
[ec nec]=bwlabel(~bw);  
% Array to store the location coordinates of objects
Y=[];X=[];              
% Finding Objects
for n=1:nec
    % Select object n
    [f1 c1]=find(ec==n);      
    % Calculate left-right limit
    iz = min(c1);der= max(c1);
    % Calculate upper - lower limit
    sup= min(f1);inf= max(f1);
    % Calculate the center
    pmx=round((der+iz)/2);    
    pmy=round((inf+sup)/2);  
    % Save the coordinate of each object
    X=[X pmy];Y=[Y pmx];      
end
% Select axes to plot
axes(handles.fotografia)      
% Show image
imshow(handles.rgb);          
hold on                       
% Graph object center
plot(Y,X,'*r')                
hold off           
% ---------------------------------------------------------------------------------------------------------------
% OBJECT RECOGNITION
function count_obj_Callback(hObject, eventdata, handles)
% Call image 
bw=~handles.bw;      
% Counting connected objects
[ec nec]=bwlabel(bw);
% Variables to count the number of objects
T=0;S=0;             
C=0;R=0;            
% Loop for recognition and classification
for n=1:nec
    % Select object n
    [f1 c1]=find(ec==n); 
    % Calculate  left-right limit
    iz = min(c1);der= max(c1);
    % Calculate upper - lower limit
    sup= min(f1);inf= max(f1);
    % Segment object n
    forma=~bw(sup:inf,iz:der);
    % Add white box (to avoid correlation errors when the image is a rectangle)
    forma(:,1)      = 1;          
    forma(:,end) = 1;       
    forma(1,:)      = 1;          
    forma(end,:) = 1;       
    % Resize image (same size as the templates)
    forma=imresize(forma,[42 24]); 
    % Call the function that compares images
    [letter vd]=read_shape(forma);
    % Write the name of the recognized shape in the static-text
    set(handles.shape_t,'String',letter)
    if     vd==1  %'Triangle';
        T=T+1;
    elseif vd==2%'Star';
        S=S+1;
    elseif vd==3%'Circle';
        C=C+1;
    else        %'Rectangle';
        R=R+1;
    end
    axes(handles.axes3)
    imshow(forma)      
    axis off           
    pause(1.5)         
end
% Display the result
msgbox({['CIRCLE: ',num2str(C)],['RECTANGLE: ',num2str(R)],...
        ['STAR: ',num2str(S)],  ['TRIANGLE: ',num2str(T)]},...
        'RESULTS')
% --- Executes on button press in sel_camera.
function sel_camara_Callback(hObject, eventdata, handles)
% Open GUI to select the camera
sel_camera
% wait until
uiwait
% Bring the camera features
global id es_web_ext
handles.es_web_ext=es_web_ext;
handles.id=id;
if es_web_ext==0
    formato='YUY2_176x144';
else
    formato='RGB24_320x240';
end
try
    % Create video object
    handles.vidobj = videoinput('winvideo',id,formato);    
    % Start video object
        start(handles.vidobj);
        guidata(hObject, handles);
        % Get resolution
        vidRes = get(handles.vidobj, 'VideoResolution');
        % Get the number of bands
        nBands = get(handles.vidobj, 'NumberOfBands');
        % Show the picture on the axes
        hImage = image(zeros(vidRes(2), vidRes(1), nBands), 'Parent',...
            handles.video_cam);
        % Viewing the video
        preview(handles.vidobj,hImage);
catch
    msgbox('Check the connection of the camera','Camera')
    set(handles.video_cam,'XTick',[ ],'YTick',[ ])
end

% -------------
% Set the video input and start the video sequence
if strcmp(get(hObject,'Visible'),'off')
    try
        % Create video object
        handles.vidobj = videoinput('winvideo');        
        % Start video object
        start(handles.vidobj);
        guidata(hObject, handles);
        % Get resolution
        vidRes = get(handles.vidobj, 'VideoResolution');
        % Get the number of bands
        nBands = get(handles.vidobj, 'NumberOfBands');
        % Show the picture on the axes
        hImage = image(zeros(vidRes(2), vidRes(1), nBands), 'Parent',...
            handles.video_cam);
        % Viewing the video
        preview(handles.vidobj,hImage);
    catch
        % Show error message
        msgbox('NO CAMERA CONNECTED','WARNING')
        % Load predefined picture
        hImage = image(imread('profile.jpg'), 'Parent', handles.video_cam);
        % Show image
        axes(handles.video_cam)
        % Remove axes
        axis off
    end
end
