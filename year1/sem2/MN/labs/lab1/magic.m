function [] = magic(name)
    A = dlmread(name);
    [n m] = size(A);
    if n ~= m
        printf("Matricea nu este magica.\n")
        return
    end
    s = sum(diag(A));
    if (s ~= sum(diag(flip(A))))
        printf("Matricea nu este magica.\n")
        return
    end
    for i = 1:n
        if s ~= sum(A(i, 1:n))
            printf("Matricea nu este magica.\n")
            return
        end
        if s ~= sum(A(1:n, i))
            printf("Matricea nu este magica.\n")
            return
        end
    end
    printf("Matricea este magica.\n")