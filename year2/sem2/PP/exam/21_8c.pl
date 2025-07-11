aux(Min, [H | T], [H |TOut]) :- Min > H, !, aux(H, T, TOut).
aux(Min, [_ | T], TOut) :- aux(Min, T, TOut).
aux(_, [], []) :- !.
subDown([H | T], [H | TOut]) :- aux(H, T, TOut).