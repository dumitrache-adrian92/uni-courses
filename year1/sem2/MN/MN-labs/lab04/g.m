function A = g(A, b)
  [n n] = size(A);
  A = [A, b];
  for p = 1:n-1
    for i = p+1:n
      A(i,:) = A(i,:) - (A(i,p) / A(p,p)) * A(p,:);
    endfor
  endfor
endfunction
