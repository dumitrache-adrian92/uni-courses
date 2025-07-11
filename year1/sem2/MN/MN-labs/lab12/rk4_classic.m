function [values] = rk4_classic(df, t0, x0, h, N)
    values = [x0];
    t = t0;
    x = x0;
    
    for i = 1:N
        % Aproximam al 2-lea termen din Taylor la pasul curent si cel viitor
        k1 = h * df(t, x);
        k2 = h * df(t + h/2, x + k1/2);
        k3 = h * df(t + h/2, x + k2/2);
        k4 = h * df(t + h, x + k3);
        % x_i + (x_{i+1} - x_i), al doilea termen vine din integrare prin
        % metoda Simpson
        x = x + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        
        t += h;
        values = [values, x];
    endfor
endfunction