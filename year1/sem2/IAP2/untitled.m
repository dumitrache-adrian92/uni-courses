v=[-8:1:8]
for i = 1:14
    v(i) = cosd(i) + 1;
end
v(15:17) = 5;
std(v)
v