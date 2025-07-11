function R = Iterative(nume, d, eps)
	% Functia care calculeaza matricea R folosind algoritmul iterativ.
	% Intrari:
	%	-> nume: numele fisierului din care se citeste;
	%	-> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
	%	-> eps: eruarea care apare in algoritm.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina.
	output_precision(6);

	file = dlmread(nume); % citim tot fisierul sub format de matrice
	N = file(1, 1); % numarul de elemente
	[n m] = size(file); % marimile matricei file
	adjacency = zeros(N); % matricea de adiacenta
	k = zeros(N); % matricea diagonala cu gradul exterior al nodurilor pe diagonala

	% construire matrice de adiacenta
	for i = 2 : N + 1
		current = file(i, 1); % nodul
		k(current, current) = file(i, 2); % gradul exterior
		for j = 3 : m
			if file (i, j) ~= 0 % daca elementul e 0 e din cauza functiei dlmread deci ignoram
				% daca muchia nu duce catre acelasi nod notam in matrice
				if current ~= file(i, j)
					adjacency(current, file (i, j)) = 1;
				% altfel inseamna ca trebuie sa ignoram muchia in calculul gradului exterior al nodului
                else
					k(current, current) = k(current, current) - 1;
				end
			end
		end
	end

	% matrice stocastica, formula inghitita sincer, initial am facut cum ne-a invatat la algebra
	% semestrul trecut si am schimbat cand nu a mers (nu aia era problema, dar ramane asa pentru
	% ca e elegant)
	M = (k^(-1) * adjacency)';

	% valoarea initiala a lui R, variabila o vom folosi in continuu pentru a recalcula R
	R_prev = ones(N, 1) * (1 / N);
	while 1
		R = d * M * R_prev + ((1 - d) / N) * ones(N, 1); % formula matriceala pentru R
		if abs(R-R_prev) < eps % s-a atins gradul de eroare dorit
			break;
		end
		R_prev = R;
    end

end