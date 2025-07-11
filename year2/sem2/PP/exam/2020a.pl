filtersorted(L, LOut) :- findall(X, (member(X, L), sort(X, X)), LOut).

med(L, Med) :-  member(Med, L),
                findall(X, (member(X, L), X < Med), Less),
                findall(X, (member(X, L), X > Med), More),
                length(Less, LLen), length(More, Mlen),
                Dif is LLen - Mlen, abs(Dif, A),
                A =< 1.
