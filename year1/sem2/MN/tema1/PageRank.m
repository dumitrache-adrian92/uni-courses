function [R1 R2] = PageRank(nume, d, eps)
	% Calculeaza indicii PageRank pentru cele 3 cerinte
	% Scrie fisierul de iesire nume.out

	output_precision(6);
	output_name = strcat(nume, '.out');	% nume fisier output

	% deschidem fisierele necesare
	input = fopen(nume, 'r');
	output = fopen(output_name, 'w');

	N = fscanf(input, "%d", 1); 	% numarul de pagini

	% incepem procesul de scriere al fisierului output
	fprintf(output, "%d\n\n", N);

	% cele doua metode de calculare al PageRank-ului
	R1 = Iterative(nume, d, eps);
	R2 = Algebraic(nume, d);

	% afisarea lor
	fprintf(output, "%06f\n", R1);
	fprintf(output, "\n");
	fprintf(output, "%06f\n", R2);
	fprintf(output, "\n");

	% sortarea descrescatoare a lui R2 in PR1 si pozitiile originale ale paginilor
	% in old_pos
	[PR1 old_pos] = sort(R2, "descend");

	% determinare val1, val2
	file = dlmread(nume);
	val1 = file(N + 2, 1);
	val2 = file(N + 3, 1);

	% afisarea pozitiei sortate, originale, cat si a apartenentei a fiecarei pagini
	for i = 1:N
		fprintf(output, "%d %d %06f\n", i, old_pos(i), Apartenenta(PR1(i), val1, val2));
	end

	% inchidere fisiere
	fclose(output);
	fclose(input);
end