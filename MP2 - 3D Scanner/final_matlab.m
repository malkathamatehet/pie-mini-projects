clear s
freeports = serialportlist("available") % Shows available serial ports

%choose port used for Arduino connection
port = "COM4";

%set baudrate
baudrate = 9600;

%open connection to serial port
s = serialport(port,baudrate);

%initialize matrices to hold all values transmitted from Arduino
%size of each matrix found by multiplying the number of degrees panned
%by the number of degrees tilted

%voltages - raw sensor readings
volts = zeros(1, 1122);

%distances - transformed sensor readings
dists = zeros(1, 1122);

%pan and tilt angles
panAngles = zeros(1, 1122);
tiltAngles = zeros(1, 1122);

%initialize a timeout in case MATLAB cannot connect to the arduino
timeout = 0;
i = 1;
% main loop to read data from the Arduino, then display it%
while timeout < 10    %    % check if data was received    %    
    while s.NumBytesAvailable > 0      
        timeout = 0;   
        %get values from Arduino and split them
        values = eval(strcat('[',readline(s),']'));
        %put voltage reading into volts matrix
        volts(1, i) = values(1);

        %transform voltage into distance with calibration curve
        volt = values(1);
        dist = 3.4263e+03*exp(-0.0307*volt) + 112.2375*exp(-0.0032*volt);

        %put distance into dists matrix
        dists(1, i) = dist;        

        %put angles into corresponding matrices
        tiltAngles(1, i) = values(2);        
        panAngles(1, i) = values(3); 
        
        %increment i in order to not overwrite previous data
        i = i + 1;
    end
    pause(0.5);    
    timeout = timeout + 1;
end
%% Result

%dists = filloutliers(dists, "next")
%above needed for 2 servo code in order to filter out noise

%reshape dists into 34 x 33 matrix (total amount panned x total amount
%tilted)
distMat = reshape(dists, [34 33]); 

%Create heatmap of matrix
heatmap(distMat');
title("Heatmap of Distances to Letter (2 Servo)")