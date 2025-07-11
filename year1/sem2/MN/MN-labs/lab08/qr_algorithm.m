function [X, l, steps] = qr_algorithm(A, max_steps)
    steps = 0;
    X = eye(length(A));
    
    % QR fara deplasare
    prev_A = A;
    while 1
        [Q, R] = qr(A);
        A = R * Q;
        X = X * Q;
        
        if (++steps == max_steps || diag(A) == diag(prev_A))
            break;
        endif
        
        prev_A = A;
    endwhile
    
    l = diag(A)';
endfunction