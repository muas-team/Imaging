%% Independent Study Progress Display
%
% Jackie Weber
%
%%
function indyGUI()
% Structure to store object handles
h = struct();
global file;
file = 'OAGC.tif';

% Create the main window
hwindow = figure('Name','ENEE499 - Image Processing Project');

% Window Title
h.talk = uicontrol('Parent',hwindow,'Units','Normalized',...
    'Style','Text','FontSize',12,'FontName','Ariel','HorizontalAlignment','Center',...
    'Position',[0.0 0.75 1 0.1],...
    'String','Use the buttons to discover different portions of Jackie''s project. The lower two will open separate windows, Shape Recognition has 4 different options.');

% Create a text box for conveying average ratio

h.button1 = uicontrol('Parent',hwindow,'Units','Normalized',...     
    'Style','PushButton','Position',[0.06 0.6 0.2 0.05],...     
    'HorizontalAlignment','Center','String','Text Recognition'); % A button

h.button2 = uicontrol('Parent',hwindow,'Units','Normalized',...     
    'Style','PushButton','Position',[0.06 0.5 0.2 0.05],...     
    'HorizontalAlignment','Center','String','Color Recognition'); % A button

h.button3 = uicontrol('Parent',hwindow,'Units','Normalized',...     
    'Style','PushButton','Position',[0.06 0.4 0.2 0.05],...     
    'HorizontalAlignment','Center','String','Shape Recognition'); % A button

% Create an axis
h.ax1 = axes('Parent',hwindow,'Position',[0.25 0.33 0.4 0.35]);
[txt, conf] = alpha_rec(file);
h.image = imshow(file);
set(h.image,'Visible','off')

h.alphalabel = uicontrol('Parent',hwindow,'Units','Normalized',...
    'Style','Text','HorizontalAlignment','Center',...
    'Position',[0.25 0.69 0.4 0.035],...
    'String','Text Recognition');

h.alphatext = uicontrol('Parent',hwindow,'Units','Normalized',...
    'Style','Text','HorizontalAlignment','Center',...
    'Position',[0.25 0.27 0.4 0.035],...
    'String',strcat('Letter: ',txt,'  Confidence Level: ',num2str(round(conf,3))));

set(h.alphalabel,'Visible','off')
set(h.alphatext,'Visible','off')

[h.button1.Callback,h.button2.Callback,h.button3.Callback] = deal({@GUI_Callbacks,h});

global x;
x = 1;
function GUI_Callbacks(hObject,eventdata,h)
    shapes = {strcat('Hexagon','.tif');...
        strcat('Circle','.tif');...
        strcat('Square','.tif');...
        strcat('Triangle','.tif')};
    switch hObject
        case h.button1
            h.image.Visible = 'on';
            set(h.alphalabel,'Visible','on')
            set(h.alphatext,'Visible','on')
        case h.button2
            h.image.Visible = 'on';
            colors = color_rec(file);
            h.colortext = uicontrol('Parent',hwindow,'Units','Normalized',...
                'Style','Text','FontSize',12,'HorizontalAlignment','Left',...
                'Position',[0.63 0.53 0.35 0.15],...
                'String',colors);
            h.colorlabel = uicontrol('Parent',hwindow,'Units','Normalized',...
                'Style','Text','HorizontalAlignment','Center',...
                'Position',[0.63 0.69 0.35 0.035],...
                'String','Color Recognition');
        case h.button3
            if (x > length(shapes))
                x = 1;
            end
            h.shape = shape_find(char(shapes(x)));
            x = x + 1;
    end
end

end
