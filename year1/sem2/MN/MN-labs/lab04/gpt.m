function [A, perm] = gpt(A,b)
  [n n] = size(A);
  A = [A, b];
  perm = 1:n;
  
  for p = 1:n-1  
  Max = max(max(A(p:n,p:n)));

    for i = p:n
      ok = 0;
      for j = p:n
        if A(i,j) == Max
          ok = 1;
          break;
        endif
      endfor
        if ok == 1
          break;
        endif
    endfor
    
    [A(p,:), A(i,:)] = deal(A(i,:), A(p,:));
    [A(:,p), A(:,j)] = deal(A(:,j), A(:,p));
    [perm(p), perm(j)] = deal(perm(j), perm(p));
  
    for i = p+1:n
      A(i,:) = A(i,:) - (A(i,p) / A(p,p)) * A(p,:);
    endfor
  
  endfor
endfunction
