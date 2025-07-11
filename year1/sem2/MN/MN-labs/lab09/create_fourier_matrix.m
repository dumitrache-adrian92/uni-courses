function [F] = create_fourier_matrix(N)
    omega = exp(2 * pi * i / N);
    F = omega .^ [0:N-1]';
    F = F .^ [0:N-1]';
endfunction