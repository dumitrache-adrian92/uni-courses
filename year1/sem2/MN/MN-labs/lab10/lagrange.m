##function [yy] = lagrange(x, y, xx)
##    n = length(x);
##    L = [];
##    
##    % Calculam polinoul R(x)
##    R = 1;
##    for i = 1:n
##        R = conv(R, [1, -x(i)]);
##    endfor
##    % Calculam polinoamele f_i = R(x) / (x - x_i)
##    f = [];
##    for i = 1:n
##        [aux, ~] = deconv(R, [1, -x(i)]);
##        f = [f; aux];
##    endfor
##    
##    % Calculam polinomul Lagrange
##    P = zeros(1, length(f(1, :)));
##    for i = 1:n
##        P += y(i) .* f(i, :) ./ polyval(f(i, :), x(i));
##    endfor
##    
##    % Aflam valorile yy in punctele xx ale polinomului
##    yy = polyval(P, xx);
##endfunction

##function [yy] = lagrange(x, y, xx)
##    n = length(x);
##    L = [];
##    
##    % Calculam multiplicatorii Lagrange
##    for i = 1:n
##        aux = 1;
##        for j = 1:i-1
##            aux = conv(aux, [1, -x(j)] ./ (x(i) - x(j)));
##        endfor
##        for j = i+1:n
##            aux = conv(aux, [1, -x(j)] ./ (x(i) - x(j)));
##        endfor
##        
##        L = [L; aux];
##    endfor
##    
##    % Calculam polinomul Lagrange
##    P = cumsum(L .* y')(end, :);
##    
##    % Aflam valorile yy in punctele xx ale polinomului
##    yy = polyval(P, xx);
##endfunction

function [yy] = lagrange(x, y, xx)
    n = length(x);
    nn = length(xx);
    yy = [];
    
    for k = 1:nn
        % Calculam multiplicatorii Lagrange in punctul xx(k)
        L = [];
        for i = 1:n
            aux = [[(xx(k) - x(1:i-1)) ./ (x(i) - x(1:i-1))], [(xx(k) -...
                x(i+1:n)) ./ (x(i) - x(i+1:n))]];
            L = [L, cumprod(aux)(end)];
        endfor
        
        % Calculam yy(k)
        yy = [yy, cumsum(L .* y)(end)];
    endfor
endfunction
