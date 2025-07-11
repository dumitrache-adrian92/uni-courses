function [x, err, steps] = gauss_seidel(A, b, x0, tol, max_steps)
  n = length(A);
  prev_x = x0;
  x = x0;
  steps = 0;
  while 1
    for i=1:n
      x(i) = (b(i) - A(i,1:i-1) * x(1:i-1) - A(i,i+1:n) * prev_x(i+1:n)) / A(i,i);
    endfor
    err = norm(x - prev_x);
    if ++steps == max_steps || err < tol
      return;
    endif
    prev_x = x;
  endwhile
endfunction
