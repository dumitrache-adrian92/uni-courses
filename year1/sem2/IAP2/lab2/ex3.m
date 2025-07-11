function [pi] = ex3(m)
    pi = 0;
    for k=0:m
        pi = pi + (-1)^k/(2*k+1);
    end
%     k=0;
%     while k<=m
%         pi = pi + (-1)^k/(2*k+1);
%         k=k+1;
%     end
    pi = pi*4;
end