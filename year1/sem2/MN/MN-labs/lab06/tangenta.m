function [r, err, steps] = tangenta(f,df,r0,tol,max_steps)
  steps = 0;
  prev_r = r0;
  while 1
    r = prev_r - feval(f,prev_r) / feval(df,prev_r);
    err = norm(r-prev_r);
    if ++steps == max_steps || err < tol
      return;
    endif
    prev_r = r;
  endwhile
endfunction
