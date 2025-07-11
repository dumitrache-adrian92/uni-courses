function [lambda, x, err, steps] = mpid_rayleigh(A,x0,tol,max_steps,alfa)
  steps = 0;
  prev_x = x0;
  while 1
    M = inv(A - alfa * eye(length(A)));
    x = M * prev_x;
    x = x / norm(x);
    lambda = x' * A * x;
    err = norm(x - prev_x);
    if ++steps == max_steps || err < tol
      return;
    endif
    alfa = lambda;
    prev_x = x;
  endwhile
endfunction
