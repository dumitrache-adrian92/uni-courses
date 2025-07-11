function [x, err, steps] = jacobi(A, b, x0, tol, max_steps)
  n = length(A);
  prev_x = x0;
  x = x0;
  steps = 0;
  while 1
    for i=1:n
      x(i) = (b(i) - A(i,:) * prev_x + A(i,i) * prev_x(i)) / A(i,i);
    endfor
    err = norm(x-prev_x);
    if ++steps == max_steps || err < tol
      return;
    endif
    prev_x = x;
  endwhile
endfunction
  