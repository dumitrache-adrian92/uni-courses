function B = PR_Inv(A)
	% Functia care calculeaza inversa matricii A folosind factorizari Gram-Schmidt

	output_precision(6);
	[n m] = size(A);
	B = zeros(n);
	Q = zeros(n);
	R = zeros(n);

	% algoritmul Gram-Schmidt imbunatatit de la lab
	for i = 1:n
		R(i, i) = norm(A(:, i), 2);
		Q(:, i) = A(:, i) / R(i, i);
		R(i, i+1:n) = Q(:, i)' * A(:, i+1:n);
		A(:, i+1:n) = A(:, i+1:n) - Q(:, i) * R(i, i+1:n);
	endfor

	% Determinarea inversei:
	% am plecat de la A = Q * R
	% Q^t * A = R
	% Q^t = R * A^(-1)
	% astfel problema inversei este transformata in rezolvarea a n sisteme de forma:
	% R * col i a lui A^(-1) = col i a lui Q^t unde i = 1:n
	Q = Q';
	for i = 1:n
		B(:, i) = SST(R, Q(:, i));
	endfor
endfunction
