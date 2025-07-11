function [lambda, x, err, steps] = mpi(A,x0,tol,max_steps)
  steps = 0;
  prev_x = x0;
  inv_A = inv(A);
  while 1
    x = inv_A * prev_x;
    x = x / norm(x);
    lambda = x' * A * x;
    err = norm(x - prev_x);
    if ++steps == max_steps || err < tol
      return;
    endif
    prev_x = x;
  endwhile
endfunction
