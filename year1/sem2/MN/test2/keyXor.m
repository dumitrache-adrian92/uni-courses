function [out] = keyXor(state, key)
    out = bitxor(state, key);
end