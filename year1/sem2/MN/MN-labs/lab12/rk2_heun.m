function [values] = rk2_heun(df, t0, x0, h, N)
    values = [x0];
    t = t0;
    x = x0;
    
    for i = 1:N
        % Aproximam al 2-lea termen din Taylor la pasul curent si cel viitor
        k1 = h * df(t, x);
        t += h;
        k2 = h * df(t, x+k1);
        % x_i + (x_{i+1} - x_i), al doilea termen vine din integrare prin
        % regula trapezelor
        x = x + 0.5 * (k1 + k2);
        
        values = [values, x];
    endfor
endfunction