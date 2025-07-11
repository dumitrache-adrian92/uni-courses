function x = Thomas(a, b, c, d)
  n = length(d);
  %transf a a.i. sa avem n elemente si a1 = 0;
  a = [0; a];
  
  %op la limita
  c(1) = c(1) / b(1);
  d(1) = d(1) / b(1);
  
  %calc coef pe caz general
  for i = 2:n-1
    numitor = b(i) - a(i)*c(i-1);
    c(i) = c(i) / numitor;
    d(i) = (d(i) - a(i)*d(i-1)) / numitor;
  endfor
  d(n) = (d(n) - a(n)*d(n-1)) / (b(n) - a(n)*c(n-1));
  
  %substitutia inapoi pt rez sist de ec
  x(n) = d(n);
  for i = n-1:-1:1
    x(i) = d(i) - c(i)*x(i+1);
  endfor
  
  x = x';
endfunction
