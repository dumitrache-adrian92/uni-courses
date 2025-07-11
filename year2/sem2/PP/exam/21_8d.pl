aux(_, [], []).
aux(Max, [H | T], [H | TOut]) :- Max < H, !, aux(H, T, TOut).
aux(Max, [_ | T], TOut) :- aux(Max, T, TOut).
subUp([H | T], [H | TOut]) :- aux(H, T, TOut).