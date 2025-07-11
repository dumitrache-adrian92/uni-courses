function A = gpp(A, b)
  [n n] = size(A);
  A = [A, b];
  for p = 1:n-1
    
    Max = max(abs(A(:,p)));
    
    for k = p:n
      if abs(A(p,k)) == Max
        break;
      endif
    endfor

    [A(p,:), A(k,:)] = deal(A(k,:), A(p,:));
    
    for i = p+1:n
      A(i,:) = A(i,:) - (A(i,p) / A(p,p)) * A(p,:);
    endfor
    
  endfor
endfunction
