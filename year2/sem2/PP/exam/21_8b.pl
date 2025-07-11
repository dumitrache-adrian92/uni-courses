aux(_, [], []) :- !. % daca a gasit o solutie, sa nu mai incerce sa caute si alta
aux(Set, [H | T], [H | TOut]) :- \+ subset(H, Set), !, append(Set, H, NewSet), aux(NewSet, T, TOut).
                                                  % ^
                                                  % |
                                                  % ca sa nu mai incerce si al doilea pattern
aux(Set, [_ | T], TOut) :- aux(Set, T, TOut).

noRedundancies(Lin, Lout) :- aux([], Lin, Lout).