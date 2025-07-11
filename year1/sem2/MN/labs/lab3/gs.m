function [Q R] = gs(A)
    [m n] = size(A);
    Q = [];
    for i = 1:n
        q = A(1:m, i);
        temp = q;
        for j = 1:i-1
            s = sum (temp.*Q(:,j));
            q = q - s*Q(1:m,j);
        end
        q = q/norm(q);
        Q = [Q q];
    end
    R=transpose(Q)*A;
end
