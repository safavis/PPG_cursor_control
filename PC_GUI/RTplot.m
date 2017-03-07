function RTplot()
freq = 100;%Change it according to the setup/Configuration in HRClick
frameSize = 10;%Interms of seconds
numSample = freq*frameSize;
char_buf = [];
data = zeros(1,numSample);
tmp = [];
folder = createFolder();
% Try–catch is to prevent Matlab from crashing when the program is finished
try
    if ~isempty(instrfind)
        fclose(instrfind);
    end
    s = setup_serialport();
    filename = fullfile(folder,'ppg.txt');
    fileID = fopen(filename,'a');
    figure;
    while(true)
        if(s.BytesAvailable > 0)
            ch = fread(s,1,'uint8');
            if ch ~= 10
                char_buf(end+1) = ch;
            elseif ch == 10
                tmp(end+1) = parseData(char_buf);
                fprintf(fileID,'%lu\n',tmp(end));
                if numel(tmp) >= freq/10
                    data = update_ui(data,tmp,freq);
                    tmp=[];
                end
                char_buf=[];
            end        
        end
    end
catch
    stopasync(s);
    fclose(s); % bad
    fprintf(1, 'Sorry, you"re going to have to close out of Matlab to close the serial port\n');
    fclose(fileID);
    return
    
end
end
function y = update_ui(data,tmp,freq)
y = data( (freq/10)+1 : end );
y = [y tmp];
tic;
plot(y);
toc;
pause(.000001);
end
function s = setup_serialport()
% Initialize serial port
s = serial('COM7');
set(s, 'Terminator', 'LF'); % Default terminator is \n
set(s,'BaudRate', 115200);
set(s,'DataBits', 8);
set(s,'StopBits', 1);
%s.ByteOrder = bigEndian;
set(s, 'ByteOrder', 'bigEndian');
s.InputBufferSize = 32768;
fopen(s);
s.ReadAsyncMode = 'continuous';
end


function y =  parseData(a)
   y = str2num(char(a));
end

function folder = createFolder()
%Create folder to store last trail's data

data_root_folder = pwd;
t = datetime('now');
mon = month(t,'shortname');
day_folder = sprintf('%d-%s-%d',t.Day,mon{1},t.Year);
if(~exist(day_folder,'dir'))
    mkdir(day_folder);
end
time_folder = sprintf('%02d-%0d',t.Hour,t.Minute);
folder = fullfile(data_root_folder,day_folder,time_folder);
mkdir(folder);
end