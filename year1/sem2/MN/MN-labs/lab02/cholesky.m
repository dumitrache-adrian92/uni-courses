function L = cholesky(A)
  [n n] = size(A);
  L = zeros(n);
  for p = [1:n]
    for q = [1:p-1]
      s = 0;
      for i = [1:q-1]
        s += L(p,i)*L(q,i);
      endfor
      L(p,q) = (A(p,q) - s) / L(q,q);
    endfor
    s = 0;
    for i = [1:p-1]
      s += L(p,i)^2;
    endfor
    L(p,p) = sqrt(A(p,p) - s);
  endfor
endfunction
    