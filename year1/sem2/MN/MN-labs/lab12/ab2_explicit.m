function [values] = ab2_explicit(df, t0, x0, h, N, initial_approximator)
    t = t0 + h;
    x = initial_approximator(df, t0, x0, h, 1)(2);
    values = [x0, x];
    % f_{i-1}
    prev_f = df(t0, x0);
    
    for i = 2:N
        f = df(t, x);
        x = x + h / 2 * (3 * f - prev_f);
        
        prev_f = f;
        t += h;
        values = [values, x];
    endfor
endfunction