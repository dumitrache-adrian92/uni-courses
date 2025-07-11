function [F] = create_fft_matrix(N)
    M = N/2;
    
    omega = exp(2 * pi * i / N);
    D = diag(omega .^ [0:M-1]);
    I = eye(M);
    
    F = create_fourier_matrix(M);
    
    perm = zeros(N);
    perm(sub2ind([N, N], [1:N], [1:2:N, 2:2:N])) = 1;
    
    F = [I, D; I, -D] * blkdiag(F, F) * perm;
endfunction