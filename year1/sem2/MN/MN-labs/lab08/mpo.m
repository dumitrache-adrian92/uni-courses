function [X l] = mpo(A, tol, max_steps)
  X = [];
  l = [];
  n = length(A);
  for i = 1:n
    prev_x = rand(n,1);
    steps = 0;
    while 1
      for j = 1:size(X,2)
        prev_x -= X(:,j)' * prev_x * X(:,j);
      endfor
      x = A * prev_x;
      x = x / norm(x);
      lambda = x' * A * x;
      err = norm(x-prev_x);
      if ++steps == max_steps || err < tol
        X = [X, x];
        l = [l, lambda];
        break;
      endif
      prev_x = x;
    endwhile
  endfor
endfunction
