function [P] = vandermonde(x, y)
    n = length(x);
    % Generam A cu puterile lui x_i pe fiecare coloana i
    A = [ones(n, 1), (ones(n-1, 1) * x)'] .^ [0:n-1];
    y = y';
    
    % Rezolvam A * P = y
    P = flip(linsolve(A, y));
endfunction