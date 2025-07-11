function [x, detA] = sisteclin(A, b)
detA=det(A);
x=A\b;
end