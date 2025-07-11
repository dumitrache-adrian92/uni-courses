function G = givens_ij(A,i,j)
  [n m] = size(A);
  G = eye(n);
  if i > j  
    c = A(j,j) / sqrt(A(i,j)^2 + A(j,j)^2);
    s = -A(i,j) / sqrt(A(i,j)^2 + A(j,j)^2);
    G(j,j) = c;
    G(j,i) = -s;
    G(i,j) = s;
    G(i,i) = c;
  elseif i < j
    c = A(j,j) / sqrt(A(i,j)^2 + A(j,j)^2);
    s = A(i,j) / sqrt(A(i,j)^2 + A(j,j)^2);
    G(i,i) = c;
    G(i,j) = -s;
    G(j,i) = s;
    G(j,j) = c;
  endif
endfunction
