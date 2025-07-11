function [out] = substitute(State, SBOX)
    xbox360 = hex2dec(strsplit(SBOX));
    out = zeros(4, 4);
    for i = 1:4
        for j = 1:4
            out(i, j) = xbox360(State(i, j) + 1);
        end
    end
end