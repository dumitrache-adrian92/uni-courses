v = [304.5; 305.2; 304.9; 304.8; 305.0; 304.6; 305.1; 304.7; 304.9];
grubbs = [0, 0, 1.153, 1.463, 1.672, 1.822, 1.938, 2.032, 2.110, 2.176];
v = sort(v);
n = length(v);
mv1 = mean(v);
std1 = std(v);
v1 = (v(n) - mv1) / std1
v2 = (mv1 - v(1)) / std1
