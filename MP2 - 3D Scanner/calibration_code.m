%% Calibration Plot

%Known data - physical distances and corresponding sensor readings
cms = [30, 50, 70, 90, 110];
sensor = [407, 260, 190, 163, 145];

%Plotting known data
hold on;
plot(cms, sensor, 'bo');
axis([20, 120, 130, 420])
xlabel("Actual Distance (cms)");
ylabel("Voltage Readings (mV)");

%Use curve fitter to find coefficients
%curveFitter(sensor, cms);

%Equation from curve fitter - chose 2nd order exponential function for best
%fit
y = linspace(140, 410, 1000);
x = 3.4263e+03*exp(-0.0307*y) + 112.2375*exp(-0.0032*y);

%Plot best fit curve over known data points
plot(x, y, 'k--')

legend("Actual Points", "Line of Best Fit");
hold off;
%% Error Plot

%Knwon distances
actual_dist = [40, 60, 80, 100, 110];

%Known sensor readings
actual_sensor = [323, 210, 170, 140, 110];

%Matrix to hold predicted distances
predictions = zeros(1, 5);

%Converting sensor readings to distances with the transfer function found above 
for i = 1:5

    predictions(i) = 3.4263e+03*exp(-0.0307*actual_sensor(i)) + 112.2375*exp(-0.0032*actual_sensor(i));

end

%Plotting predicted vs. actual distances
figure()
plot(predictions, actual_dist, 'ro')
xlabel("Predicted Distances (cm)")
ylabel("Actual Distances (cm)")


