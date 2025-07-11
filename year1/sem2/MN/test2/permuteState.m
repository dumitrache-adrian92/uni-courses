function [State] = PermuteState(State, KeyS)
    perm = gpp(KeyS, zeros(16, 1));
    State = State * perm;
end