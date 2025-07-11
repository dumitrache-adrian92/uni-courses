function [L U] = doolittle(A)
    %Implementare a descompunerii Doolittle LU
    [n m] = size(A);
    L = eye(n);
    U = zeros(n);
    for i = 1:n
        for k = i:n
            U(i,k) = A(i,k) - L(i,1:i) * U(1:i,k);
        end
        for k = i+1:n
            L(k,i) = (A(k,i) - L(k,1:i) * U(1:i,i)) / U(i,i);
        end
    end
end