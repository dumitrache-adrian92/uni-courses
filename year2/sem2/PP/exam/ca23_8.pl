extract(Elem, [Elem | L], L).
extract(Elem, [_ | L], L2) :- extract(Elem, L, L2).

combs(0, _, []) :- !.
combs(K, L, [H | L2]) :- extract(H, L, Rest), KDec is K - 1, combs(KDec, Rest, L2).