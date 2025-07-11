function A = bicubic_coef(f, Ix, Iy, Ixy, x1, y1, x2, y2)
    % =========================================================================
    % Calculeaz? coeficien?ii de Interpolare Bicubic? pentru 4 puncte al?turate
    % =========================================================================

    % TODO: Calculeaz? matricile intermediare.
    m1 = [1, 0, 0, 0; 0, 0, 1, 0; -3, 3, -2, -1; 2, -2, 1, 1];

    m2(:, 1) = [f(y1, x1), f(y1, x2), Ix(y1, x1), Ix(y1, x2)];
    m2(:, 2) = [f(y2, x1), f(y2, x2), Ix(y2, x1), Ix(y2, x2)];
    m2(:, 3) = [Iy(y1, x1), Iy(y1, x2), Ixy(y1, x1), Ixy(y1, x2)];
    m2(:, 4) = [Iy(y2, x1), Iy(y2, x2), Ixy(y2, x1), Ixy(y2, x2)];

    m3 = [1, 0, -3, 2; 0, 0, 3, -2; 0, 1, -2, 1; 0, 0, -1, 1];
    % TODO: Converte?te matricile intermediare la double.
    m1 = double(m1);
    m2 = double(m2);
    m3 = double(m3);
    % TODO: Calculeaz? matricea final?.
    A = m1 * m2 * m3;
endfunction