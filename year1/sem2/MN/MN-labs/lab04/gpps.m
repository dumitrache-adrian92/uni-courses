function A = gpps(A, b)
  [n n] = size(A);
  A = [A, b];
  for p = 1:n-1
    
    % factorii de scalare
    s = zeros(n,1);
    for i = p:n
      s(i) = max(abs(A(i,p:n)));
    endfor
    
    Max = max(abs(A(p:n,p) ./ s(p:n)));
    
    for k = p:n
      if abs(A(k,p) / s(k)) == Max
        break;
      endif
    endfor
    
    [A(p,:), A(k,:)] = deal(A(k,:), A(p,:));
    
    for i = p+1:n
      A(i,:) = A(i,:) - (A(i,p) / A(p,p)) * A(p,:);
    endfor
    
  endfor
endfunction
