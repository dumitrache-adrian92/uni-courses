counts(L, LOut) :- findall([N | T], (member(T, L), sort(T, TSet), length(TSet, N)), LOut).

heads(L, Limit, LOut) :- findall(X, (member([X | R], L), sort(R, L2Set), length(L2Set, L2SetLen), L2SetLen > Limit), LOut).

index(L, Index) :- findall((Elem, Count), (member(Elem, L), findall(Lol, (member(Lol, L), Elem = Lol), Lol2), length(Lol2, Count)), Index).

singles(List, Singles) :- setof(E,
                            L^(member(E, List),
                            findall(X, (member(X, List), E = X), L), length(L, 1)),
                            Singles).