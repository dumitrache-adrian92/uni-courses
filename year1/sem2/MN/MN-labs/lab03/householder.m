function [Q R] = householder(A)
  [n m] = size(A);
  Q = eye(n);
  if n <= m
    count = n - 1;
  else
    count = m;
  endif
  for i = 1:count
    v = zeros(n,1);
    v(i+1:n) = A(i+1:n,i);
    v(i) = A(i,i) + sign(A(i,i)) * norm(A(i:n,i));
    H = eye(n) - (2 * v * v') / (v' * v);
    A = H * A;
    Q = Q * H';
    R = A;
  endfor
endfunction
  