function [S] = spline_c2_natural(x, y)
    n = length(x);
    A = [];
    b = [];
    
    % Generam sistemul de ecuatii
    % Pas 1:
    % S_i(x_i) = y_i
    for i = 1:n-1
        A = [A; [zeros(1, (i-1)*4), 1, zeros(1, (n-i-1)*4+3)]];
        b = [b; y(i)];
    endfor
    % S_{n-1}(x_n) = y_n
    aux = x(n) - x(n-1);
    A = [A; [zeros(1, (n-2)*4), 1, aux, aux^2, aux^3]];
    b = [b; y(n)];
    
    % Pas 2:
    % S_i(x_{i+1}) = S_{i+1}(x_{i+1})
    for i = 1:n-2
        aux = x(i+1) - x(i);
        A = [A; [zeros(1, (i-1)*4), 1, aux, aux^2, aux^3, -1,...
            zeros(1, (n-i-2)*4+3)]];
        b = [b; 0];
    endfor
    
    % Pas 3:
    % S_i'(x_{i+1}) = S_{i+1}'(x_{i+1})
    for i = 1:n-2
        aux = x(i+1) - x(i);
        A = [A; [zeros(1, (i-1)*4), 0, 1, 2*aux, 3*aux^2, 0, -1,...
            zeros(1, (n-i-2)*4+2)]];
        b = [b; 0];
    endfor
    
    % Pas 4:
    % S_i''(x_{i+1}) = S_{i+1}''(x_{i+1})
    for i = 1:n-2
        aux = x(i+1) - x(i);
        A = [A; [zeros(1, (i-1)*4), 0, 0, 2, 6*aux, 0, 0, -2,...
            zeros(1, (n-i-2)*4+1)]];
        b = [b; 0];
    endfor
    
    % Pas 5:
    % S_1''(x_1) = S_{n-1}''(x_n) = 0;
    A = [A; [0, 0, 1, 0, zeros(1, (n-2)*4)]];
    A = [A; [zeros(1, (n-2)*4), 0, 0, 2, 6*(x(n) - x(n-1))]];
    b = [b; 0; 0];
    
    S = linsolve(A, b);
    S = reshape(S, 4, n-1)';
endfunction