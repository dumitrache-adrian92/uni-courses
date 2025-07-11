function [ok] = magicmat(A)
  n = length(A);
  suma = sum([1:n^2])/n;
  ok = 1;
  
  for i = [1:n]
    s = 0;
    for j = [1:n]
      s = s+A(i,j);
    endfor
    if s!= suma
      ok = 0;
    endif
  endfor
  
  for j = [1:n]
    s = 0;
    for i = [1:n]
      s = s+A(i,j);
    endfor
    if s!= suma
      ok = 0;
    endif
  endfor
endfunction
