function [sum] = sumaImpareFor()
    var = input('Introduceti variabila:');
    sum = 0;
    for i = 1:2:var
        sum = sum+i;
    end