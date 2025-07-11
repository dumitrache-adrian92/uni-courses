function [Q R] = givens(A)
  [n m] = size(A);
  Q = eye(n);
  for j = 1:n-1
    for i = j+1:n
      G = eye(n);
      c = A(j,j) / sqrt(A(i,j)^2 + A(j,j)^2);
      s = -A(i,j) / sqrt(A(i,j)^2 + A(j,j)^2);
      G(j,j) = c;
      G(j,i) = -s;
      G(i,j) = s;
      G(i,i) = c;
      A = G * A;
      Q = Q * G';
    endfor
  endfor
  R = A;
endfunction