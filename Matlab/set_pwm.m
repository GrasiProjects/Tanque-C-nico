function x = set_pwm(duty)
global SerPIC
fprintf(SerPIC,'%c','p') ;
if duty>100
    duty = 100;
end
if duty<0
    duty = 0;
end
% duty = (251)*(duty/100);
dutyy = num2str(duty);
fprintf(SerPIC, '%s\n', dutyy);
end