function y = Apartenenta(x, val1, val2)
	% Functia care primeste ca parametrii x, val1, val2 si care calculeaza valoarea functiei membru in punctul x.
	% Stim ca 0 <= x <= 1

	output_precision(6);

	% valorile lui a si b determinate prin urmatoarea metoda:
	% cum a si b trebuie alese astfel incat functia u sa fie continua, putem reduce
	% problema la rezolvarea unui sistem:
	% u este continua in toate punctele inafara de val1 si val2
	% continuitate in val1 daca a * val1 + b = 0
	% continuitate in val2 daca a * val2 + b = 1
	% deci avem un sistem simplu cu 2 necunoscute din care deducem formulele urmatoare:
	a = 1 / (val2 - val1);
	b = - (val1 / (val2 - val1));

	% determinarea valorii lui u in functie de fiecare element din x
	if x < val1
		y = 0;
	elseif x >= val1 && x <= val2
		y = x * a + b;
	else
		y = 1;
	end
end

