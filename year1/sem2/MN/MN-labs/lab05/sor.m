function [x, err, steps] = sor(A,b,w,x0,tol,max_steps)
  D = diag(diag(A));
  L = tril(A) - D;
  U = A - tril(A);
  N = D + w * L;
  P = (1 - w) * D - w * U;
  inv_N = inv(N);
  G = inv_N * P;
  c = w * inv_N * b;
  prev_x = x0;
  steps = 0;
  while 1
    x = G * prev_x + c;
    err = norm(x - prev_x);
    if ++steps == max_steps || err < tol
      return;
    endif
    prev_x = x;
  endwhile
endfunction
