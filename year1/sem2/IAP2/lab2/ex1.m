function [f] = ex1(t)
    if t<0
        f = 0;
    elseif t>1
        f = 1;
    else
        f = t * t * (3 - 2 * t);
    end
end