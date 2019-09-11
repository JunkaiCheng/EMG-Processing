clear all
clc
m = load('data.txt');
AVG = load('movingAVG_result.txt');
%Rectifier = load('Rectifier_result.txt');
%RMS = load ('RMSFilter_result.txt');
plot(m(1,:));
hold on
%plot(RMS(1,:));
hold on
plot(AVG(1,:));
%hold on
%plot(Rectifier(1,:));