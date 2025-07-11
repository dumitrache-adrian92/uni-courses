function [S] = simpson(f, a, b, n)
    % Gasim punctele x echidistante in care calculam functia
    step = (b-a) / (2*n);
    x = [a:step:b];
    y = f(x);
    
    % Insumam conform regulei Simpson
    S = y(1) + y(end) + 4 * sum(y(2:2:end-1)) + 2 * sum(y(3:2:end-1));
    S = step / 3 * S;
endfunction
