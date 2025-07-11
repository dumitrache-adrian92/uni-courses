function [lambda, x, err, steps] = mpd(A,x0,tol,max_steps)
  steps = 0;
  prev_x = x0;
  while 1
    x = A * prev_x;
    x = x / norm(x);
    lambda = x' * A * x;
    err = norm(x-prev_x);
    if ++steps == max_steps || err < tol
      return;
    endif
    prev_x = x;
  endwhile
endfunction
