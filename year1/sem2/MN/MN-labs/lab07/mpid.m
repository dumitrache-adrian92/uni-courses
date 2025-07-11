function [lambda, x, err, steps] = mpid(A,x0,tol,max_steps,alfa)
  steps = 0;
  prev_x = x0;
  M = inv(A - alfa * eye(length(A)));
  while 1
    x = M * prev_x;
    x = x / norm(x);
    lambda = x' * A * x;
    err = norm(x - prev_x);
    if ++steps == max_steps || err < tol
      return;
    endif
    prev_x = x;
  endwhile
endfunction
