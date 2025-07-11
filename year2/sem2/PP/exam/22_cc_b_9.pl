checkRest(Current, [H | T], [H | TDown]) :- H < Current, checkRest(H, T, TDown).
checkRest(Current, [H | T], [HDown | TDown]) :- H >= Current, checkRest(Current, T, [HDown | TDown]).
checkRest(_, [], []).
dn([H | T], [H | TL]) :- checkRest(H, T, TL).