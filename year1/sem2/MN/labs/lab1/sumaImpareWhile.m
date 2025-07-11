function [sum] = sumaImpareWhile()
    var = input('Introduceti variabila:');
    sum = 0;
    i = 1;
    while i<var
        sum = sum + i;
        i = i + 2;
    end