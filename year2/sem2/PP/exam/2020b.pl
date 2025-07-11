aux(_, _, 0, []) :- !.

aux(L, [H | T], R, [H | TOut]) :- RDec is R - 1, aux(L, T, RDec, TOut).
aux(L, [], R, TOut) :- aux(L, L, R, TOut).

gen(L, R, Out) :- aux(L, L, R, Out).

minmax(L, Min, Max) :- setof(X, (member(X, L)), [Min | R]),
                        reverse(R, [Max | _]).