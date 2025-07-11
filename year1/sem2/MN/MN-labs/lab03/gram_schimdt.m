function [Q R] = gram_schimdt(A)
  [n n] = size(A);
  Q = zeros(n,n);
  for i = 1:n
    s = zeros(n,1);
    for j = 1:i-1
      s = s + (A(:,i)' * Q(:,j)) / (Q(:,j)' * Q(:,j)) * Q(:,j);
    endfor
    u = A(:,i) - s;
    Q(:,i) = u / norm(u);
  endfor
  R = Q' * A;
endfunction
