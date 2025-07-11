%citire date
[date,text] = xlsread('Date_temp.xls')
%extragere date de temperatura
x = date';
sort(x);
%calcul medie aritmetica
med_aritm = mean(x);
%estimatia=deviatia standard
estimatia = std(x);
dimensiune = length(x);
%creare histograma
figure(1)
hist(x)
title('Histograma_31_initial')
%testul 3sigma
y = [];
xx = [];
for i = 1:dimensiune
if x(i) > med_aritm + 3 * estimatia
    y = [y x(i)];
elseif x(i) < med_aritm - 3 * estimatia
    y = [y x(i)];
else xx = [xx x(i)];
end
end
%calcul medie aritmetica noua
med_aritm_nou = mean(xx);
%estimatia=deviatia standard noua
estimatia_nou = std(xx);
dimensiunex = length(xx);
%creare histograma
figure(2)
hist(xx)
mean(xx)
std(xx)
title('Histograma_31_date_corecte')