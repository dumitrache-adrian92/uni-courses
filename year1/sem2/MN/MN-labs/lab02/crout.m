function [L U] = crout(A)
  [n n] = size(A);
  U = eye(n);
  L = zeros(n);
  for p = [1:n]
    for q = [1:p]
      s = 0;
      for i = [1:q-1]
        s += L(p,i)*U(i,q);
      endfor
      L(p,q) = A(p,q) - s;
    endfor
    for q = [p+1:n]
      s = 0;
      for i = [1:p-1]
        s += L(p,i)*U(i,q);
      endfor
      U(p,q) = (A(p,q) - s) / L(p,p);
    endfor
  endfor
endfunction
