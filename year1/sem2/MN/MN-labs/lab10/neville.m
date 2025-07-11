    function [yy] = neville(x, y, xx)
        n = length(y);
        % Pentru a paraleliza calculul in toate punctele xx
        y = ones(length(xx), 1) * y;
        
        % i etape de combinari de P (dupa un pas i, vom avea polinoame de gard i)
        for i = 1:n-1
            % Combinarile de 2 P intr-un P de grad mai mare
            [~, m] = size(y);
            for j = 1:m-1
                % Fiecare linie k contine P de grad curent, i-1, in punctul xx(k)
                y(:, j) = ((xx' - x(j+i)) .* y(:, j) - (xx' - x(j)) .* y(:, j+1)) ./ (x(j) - x(j+i));
            endfor
            y = y(:, 1:(end-1));
        endfor
        
        yy = y';
    endfunction