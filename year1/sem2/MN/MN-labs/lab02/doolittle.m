function [L U] = doolittle(A)
  [n n] = size(A);
  L = eye(n);
  U = zeros(n);
  for q = [1:n]
    for p = [1:q]
      s = 0;
      for i = [1:p-1]
        s += L(p,i)*U(i,q);
      endfor
      U(p,q) = A(p,q) - s;
    endfor
    for p = [q+1:n]
      s = 0;
      for i = [1:q-1]
        s += L(p,i)*U(i,q);
      endfor
      L(p,q) = (A(p,q) - s) / U(q,q);
    endfor
  endfor
endfunction
