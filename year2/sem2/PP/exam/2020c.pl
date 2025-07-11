a([], _, _, []).
a(_, [], _, []).
a(_, _, [], []).

a([X | R1], [Y | R2], [Z | R3], [(X, Y, Z) | R]) :- a(R1, R2, R3, R).

secondMin(L, SecondMin) :- setof(X, member(X, L), [_ | [SecondMin | _]]).