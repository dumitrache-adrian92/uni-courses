function [T] = trapezoidal(f, a, b, n)
    % Gasim cele n+1 puncte x echidistante in care calculam functia
    step = (b-a) / n;
    x = [a:step:b];
    y = f(x);
    
    % Insumam trapezele generate de x_i si x_{i+1} cu i de la 1 la n
    T = sum(y(1:end-1) + y(2:end)) .* step / 2;
endfunction