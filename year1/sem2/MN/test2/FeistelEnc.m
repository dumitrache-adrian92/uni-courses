function [state] = FeistelEnc(R,key,SBOX)
    state = double(R);
    keyState = reshape(double(key), 4, 4);
    a = mod(length(state), 16);
    a = 16 - length(state);
    length(state);
    if a > 0
        for i = 2:a
            state(length(state) + i) = 0;
        end
    end
    left = reshape(state(1:16), 4, 4);
    right = reshape(state(17:32), 4, 4);
    n = 3;
    for i = 1:n
        if mod(i, 2) == 1
            right = keyXor(right, keyState);
            right = substitute(right, SBOX);
            permuteState(right, keyState);
            right = substitute(right, SBOX);
            permuteState(right, keyState);
        else
            left = keyXor(left, keyState);
            left = substitute(left, SBOX);
            permuteState(left, keyState);
            left = substitute(left, SBOX);
            permuteState(left, keyState);
        end
        bitxor(left, right);
    end

end