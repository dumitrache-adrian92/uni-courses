checkRest(Current, [H | T], [H | TUp]) :- H > Current, checkRest(H, T, TUp).
checkRest(Current, [H | T], Up) :- H =< Current, checkRest(Current, T, Up).
checkRest(_, [], []).
up([H | T], [H | TUp]) :- checkRest(H, T, TUp).