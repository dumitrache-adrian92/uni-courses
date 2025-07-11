function [R] = romberg(f, a, b, n)
    R = [];
    
    % Calculam R(0:n, 0) cu regula trapezelor
    for i = 0:n
        R = [R, trapezoidal(f, a, b, bitshift(1, i))];
    endfor
    
    for m = 1:n
        prev_R = R;
        % Calculam coloana m
        R = prev_R(2:end) + (prev_R(2:end) - prev_R(1:end-1)) ./...
            (bitshift(1, 2*m) - 1);
    endfor
endfunction