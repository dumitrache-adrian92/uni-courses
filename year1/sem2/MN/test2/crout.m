function [L U] = crout(A)
    %Implementare a descompunerii Crout LU
    [n m] = size(A);
    L = zeros(n,n);
    U = eye(n);
    for p = 1:n
        for i = p:n
            L(i,p) = A(i,p) - L(i,1:p-1) * U(1:p-1,p);
        end
        for j = p+1:n
            U(p,j) = (A(p,j) - L(p,1:p-1) * U(1:p-1,j)) / L(p,p);
        end
    end
end