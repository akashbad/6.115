function y = spin_dude(varargin)

%SPIN_DUDE  Collects data from 6.115 tomography device
%  
%  Run SPIN_DUDE in the matlab command window to collect data
%  from the tomography device.
%  
%  SPIN_DUDE has an internal call to INV_RADON which takes the
%  collected data and produces the cross section of the objects
%  placed in the device.
%  
%
%  Type "spin_dude('a')" to run ARI_INV_RADON for processing
%
%  Type "spin_dude('m')" to run MAT_INV_RADON for processing
%  
%
%  If necessary, the serial COM port can be passed to SPIN_DUDE
%  as a second argument.
%
%  Typing "spin_dude('a', 'COM2') for example will use ARI_INV_RADON
%  for processing and select COM2 as the COM port for serial I/O
%
%
%  Typing "spin_dude" with no arguments defaults to using ARI_INV_RADON, and COM1
%
%
%  Ariel Rodriguez
%  MIT LEES
%  July 2003
%
%
%  See also ARI_INV_RADON, MAT_INV_RADON, AR_ROTATE_BL, AR_ROTATE_NN

args=nargin;

% Make sure the serial port is really really really closed.
ports=instrfind;
if size(ports,1) > 0 
    stopasync(instrfind);
    fclose(instrfind);
    delete(instrfind);
end

if args > 2
    error('Too many arguments.  Spin_dude expects one argument either ''m'' or ''a''');
    return
elseif args == 2
    x=varargin{1};
    port=varargin(2);
elseif args==1
    x=varargin{1};
    port='/dev/tty.usbserial';
else
    x='a';
    port='/dev/tty.usbserial';
end

% Take a look at the input argument to detect which flavor of INV_RADON to run
switch x
case 'a'
    INV_RADON = @ari_inv_radon;
case 'm'
    error('This is the student version of MATLAB, image processing toolbox unavailable')
    INV_RADON = @mat_inv_radon;
otherwise
    error('Invalid first argument to spin_dude'); % Need to catch invalid inputs
end

s=serial(port, 'BaudRate', 9600, 'DataBits', 8, 'Parity', 'none', 'StopBits', 1, 'Terminator', 'LF'); % create a serial port object

matrix=double([]); % initialize the image matrix
fopen(s); % open the serial port
flushinput(s); % flush the serial port buffer before collecting new data
fprintf(s,' '); % send a framing character to connect with it
fprintf(s,' '); % send a space character to the R31JP to start reading data

% Data collection loop
% Unfortunately at the moment, it is a fixed loop of 24 samples.  Later on we may add an argument
% to tell SPIN_DUDE what angle settings you want, but for right now it's set at 24, 15 degree rotations
for i=1:24
    collected = double(fscanf(s,'%x')); % Read the data
    matrix = horzcat(matrix, collected) % Add rows to the input matrix for INV_RADON
end

% Close and wrap up the serial port
stopasync(s);
fclose(s);
delete(s);
clear s;

% Set up the angles to be given to either flavor of INV_RADON
ang = [0:15:360]; % the angles

feval(INV_RADON,matrix,ang)
