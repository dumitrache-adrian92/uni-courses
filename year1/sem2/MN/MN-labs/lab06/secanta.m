function [r, err, steps] = secanta(f,r0,r1,tol,max_steps)
  steps = 0;
  prev_prev_r = r0;
  prev_r = r1;
  while 1
    r = prev_r - feval(f,prev_r) * (prev_r - prev_prev_r) / (feval(f,prev_r) - feval(f,prev_prev_r));
    err = norm(r - prev_r);
    if ++steps == max_steps || err < tol
      return;
    endif
    prev_prev_r = prev_r;
    prev_r = r;
  endwhile
endfunction
