function [X l] = iterare_ortogonala(A, tol, max_steps)
  n = length(A);
  prev_U = rand(n);
  steps = 0;
  while 1
    [Q, R] = qr(prev_U);
    U = A * prev_U;
    for j = 1:n
      U(:,j) = U(:,j) / norm(U(:,j));
    endfor
    for j = 1:n
      err(j) = norm(U(:,j) - prev_U(:,j));
    endfor
    if ++steps == max_steps || max(err) < tol
      [Q, R] = qr(U);
      X = Q;
      l = diag(Q'*A*Q);
      return;
    endif
    prev_U = U;
  endwhile
endfunction
