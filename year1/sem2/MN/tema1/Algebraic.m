function R = Algebraic(nume, d)
	% Functia care calculeaza vectorul PageRank folosind varianta algebrica de calcul.
	% Intrari:
	%	-> nume: numele fisierului in care se scrie;
	%	-> d: probabilitatea ca un anumit utilizator sa continue navigarea la o pagina urmatoare.
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

	% derivarea formulei algebrice pentru vectorul pagerank
	% R = [(1 - d) / N, ..., (1 - d) / N]^t + d * M * R
	% (In - d * M) * R = [(1 - d) / N, ..., (1 - d) / N]^t
	% R = (In - d * M)^(-1) * [(1 - d) / N, ..., (1 - d) / N]^t
	% deci trebuie sa calculam inversa lui In - d * M si apoi avem o formula directa
	inv = PR_Inv(eye(N) - d * M);
	R = inv * (ones(N, 1) * ((1 - d) / N));
end